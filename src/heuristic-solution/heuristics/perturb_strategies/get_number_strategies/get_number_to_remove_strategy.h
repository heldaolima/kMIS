#ifndef __get_number_to_remove_stg_h__
#define __get_number_to_remove_stg_h__

enum NumberToRemoveEstrategyEnum {
  ROOT_OF_K,
  RANDOM_PROPORTION
};

class GetNumberToRemoveStrategy {
public:
  virtual int getNumber(int k) const = 0;
  virtual void print() = 0;
  virtual ~GetNumberToRemoveStrategy();
};

#endif
