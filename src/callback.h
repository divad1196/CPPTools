#ifndef CPPTOOLS_CALLBACK_H
#define CPPTOOLS_CALLBACK_H

#include <functional>
#include <vector>
#include <chrono>
#include <atomic>
#include <mutex>

template<typename T>
class Wrapper {
    public:
        using Getter = std::function<T(const T& value)>;
        using Setter = std::function<T(const T& value, const T& new_value)>;
        using SimpleSetter = std::function<T(const T& new_value)>;
        
        Wrapper(
            const T& value,
            const Getter& getter,
            const Setter& setter = [](const T& value __attribute__((unused)), const T& new_value) {return new_value;}
        ):  _inner(value), _getter(getter), _setter(setter) {}
        
        Wrapper(
            const T& value,
            const Getter& getter,
            const SimpleSetter& setter
        ):  Wrapper(value, getter,
            [&setter](const T& value __attribute__((unused)), const T& new_value){
                return setter(new_value);
            }
        ) {}

        T get() const {
            return _getter(_inner);
        }
        
        Wrapper& set(const T& value) {
            _inner = _setter(_inner, value);
            return *this;
        }

        Wrapper& operator=(const T& value) {
            return set(value);
        }

        operator T() {
            return get();
        }

    private:
        T _inner;
        Getter _getter;
        Setter _setter;
};

namespace {
    std::mutex THREADED_WRAPPER_GLOBAL_MUTEX;
}
template<typename T>
class ThreadedWrapper: Wrapper<T> {
    using super = Wrapper<T>;
    public:
        using Getter = typename super::Getter;
        using Setter = typename super::Setter;
        using SimpleSetter = typename super::SimpleSetter;

        ThreadedWrapper(
            std::mutex& wmutex,
            const T& value,
            const Getter& getter,
            const Setter& setter = [](const T& value __attribute__((unused)), const T& new_value) {return new_value;}
        ): super(value, getter, setter), _mutex(wmutex) {}

        ThreadedWrapper(
            std::mutex& wmutex,
            const T& value,
            const Getter& getter,
            const SimpleSetter& setter
        ): super(value, getter, setter), _mutex(wmutex) {}

        ThreadedWrapper(
            const T& value,
            const Getter& getter,
            const Setter& setter = [](const T& value __attribute__((unused)), const T& new_value) {return new_value;}
        ): ThreadedWrapper(THREADED_WRAPPER_GLOBAL_MUTEX, value, getter, setter) {}

        ThreadedWrapper(
            const T& value,
            const Getter& getter,
            const SimpleSetter& setter
        ): ThreadedWrapper(THREADED_WRAPPER_GLOBAL_MUTEX, value, getter, setter) {}

        T get() const {
            std::lock_guard<std::mutex> guard(_mutex);
            return this->get();
        }
        
        ThreadedWrapper& set(const T& value) {
            // FIXME: one thread trying multiple access block itself
            // https://en.cppreference.com/w/cpp/thread/recursive_mutex
            // Use try_lock?
            std::lock_guard<std::mutex> guard(_mutex);
            return this->set(value);
        }
        
        ThreadedWrapper& operator=(const T& value) {
            return set(value);
        }

        operator T() {
            return get();
        }

    private:
        std::mutex& _mutex;
};


template<typename T>
class AtomicWrapper: Wrapper<std::atomic<T>> {};

template<typename T>
class Subject: Wrapper<T> {
    using super = Wrapper<T>;
    public:
        using Getter = typename super::Getter;
        using Setter = typename super::Setter;

        using Callback = std::function<void(const T& value)>;
        using CallbackList = std::vector<Callback>;


        Subject(
            const T& value,
            const Getter& getter,
            const Setter& setter,
            const CallbackList& subscriptions = {}
        ): super(value, getter, setter), _subscriptions(subscriptions) {}
        
        Subject(
            const T& value,
            const Getter& getter,
            const CallbackList& subscriptions = {}
        ): super(value, getter), _subscriptions(subscriptions) {}

        Subject(
            const T& value,
            const CallbackList& subscriptions = {}
        ): super(value, [](const T& value){ return value; }), _subscriptions(subscriptions) {}

        void subscribe(const Callback& callback) {
            _subscriptions.push_back(callback);
        }

        void forEach(const T& value) {
            for(const auto& callback: _subscriptions) {
                callback(value);
            }
        }

        void propagate() {
            forEach(this->get());
        }

        void set(const T& value) {
            super::set(value);
            propagate();
        }
    private:
        CallbackList _subscriptions;
};

template<typename Duration>
class BInterval {
    using Clock = std::chrono::high_resolution_clock;
    using Unit = std::chrono::milliseconds;

    public:
        using type = decltype(Clock::now());
        using TimedCallBack = std::function<void(Duration)>;
        using CallBack = std::function<void(void)>;

        BInterval(Duration interval): _interval(interval) {}

        static BInterval Seconds(int seconds) {
            return BInterval(seconds * 1000);
        }

        static BInterval Minutes(int minutes) {
            return Seconds(minutes * 60);
        }

        static BInterval FPS(int fps) {
            return BInterval(1000 / fps);
        }

        void runWhile(const TimedCallBack& callback, const bool& sentinel) {
            type last(now());
            Duration elapsed = 0;
            while(sentinel) {
                type current = now();
                Duration dt = delta(last, current);
                if(dt) {
                    elapsed += dt;
                    last = current;
                }
                while(elapsed > _interval) {
                    elapsed -= _interval;
                    callback(_interval);
                }
            }
        }

        void runWhile(const CallBack& callback, const bool& sentinel) {
            runWhile(toTimed(callback), sentinel);
        }

        void runFor(const TimedCallBack& callback, Duration duration) {
            bool sentinelle = true;
            runWhile(
                [&duration, &sentinelle, &callback](Duration delta) {
                    callback(delta);
                    sentinelle = (duration -= delta) > 0;
                },
                sentinelle
            );
        }

        void runFor(const CallBack& callback, Duration duration) {
            runFor(toTimed(callback), duration);
        }

        void run(const TimedCallBack& callback) {
            bool sentinelle = true;
            runWhile(callback, sentinelle);
        }


        void run(const CallBack& callback) {
            run(toTimed(callback));
        }

    private:

        static TimedCallBack toTimed(const CallBack& callback) {
            return [&callback](Duration duration __attribute__((unused))) {
                callback();
            };
        }

        static type now() {
            return Clock::now();
        }

        static Duration delta(type first, type second) {
            return (Duration)std::chrono::duration_cast<Unit>(second - first).count();
        }

        Duration _interval;
};

using Interval = BInterval<double>;

template<typename Duration>
class BDebounce {
    using Clock = std::chrono::high_resolution_clock;
    using Unit = std::chrono::milliseconds;

    public:
        using type = decltype(Clock::now());

        BDebounce(Duration interval): _interval(interval) {
            reset();
        }

        static BDebounce Seconds(int seconds) {
            return BDebounce(seconds * 1000);
        }

        static BDebounce Minutes(int minutes) {
            return Seconds(minutes * 60);
        }

        void reset() {
            _last = now() - Unit((int)_interval);
        }

        bool check() {
            type current = now();
            Duration dt = delta(_last, current);
            if(dt < _interval) {
                return false;
            }
            _last = current;
            return true;
        }

        operator bool() {
            return check();
        }

    private:
        static type now() {
            return Clock::now();
        }

        static Duration delta(type first, type second) {
            return (Duration)std::chrono::duration_cast<Unit>(second - first).count();
        }

        Duration _interval;
        type _last;
};


using Debounce = BDebounce<double>;

template<typename T, typename N=T>
class Aggregate {
    public:
        using Func = std::function<T(const T& aggr, const N& value)>;
        Aggregate(const T& initial, const Func& f): _value(initial), _func(f) {}
        Aggregate(const Func& f): Aggregate(T(), f) {}

        const T& get() const {
            return _value;
        }

        const T& next(const N& value) {
            return _value = _func(get(), value);
        }

        const T& operator()() {
            return get();
        }
        const T& operator()(const N& value) {
            return next(value);
        }

    private:
        T _value;
        Func _func;
};

#endif  // CPPTOOLS_CALLBACK_H