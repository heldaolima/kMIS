#ifndef __stop_strategy_h__
#define __stop_strategy_h__

class StopStrategy {
public:
  virtual void init() = 0;
  virtual bool stopCondition() = 0;
  virtual void update() = 0;
  virtual void print() const = 0;
  virtual ~StopStrategy();
};

#endif
