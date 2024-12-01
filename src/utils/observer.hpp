#include <algorithm>
#include <vector>

#ifndef F_OBSERVER
#define F_OBSERVER

template <typename T> class IListener {
public:
  virtual void update(T Data) = 0;
};

template <typename T> class IEmitter {

public:
  void addListener(IListener<T> *listener) { listeners.push_back(listener); }

  void removeListener(IListener<T> *listener) {
    listeners.erase(std::remove(listeners.begin(), listeners.end(), listener),
                    listeners.end());
  }

private:
  std::vector<IListener<T> *> listeners;

protected:
  void emit(T event) {
    for (IListener<T>* listener : listeners)
      listener->update(event);
  }
};

#endif
