#ifndef __get_number_to_remove_stg_h__
#define __get_number_to_remove_stg_h__

class GetNumberToRemoveStrategy {
public:
  virtual ~GetNumberToRemoveStrategy();
  virtual int getNumber(int k) const = 0;
};

#endif
