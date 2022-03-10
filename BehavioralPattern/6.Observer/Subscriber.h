#ifndef SUBSCRIBER_H_
#define SUBSCRIBER_H_

class AbstractObserver {
 public:
    virtual void response() = 0;
};

#endif  // SUBSCRIBER_H_