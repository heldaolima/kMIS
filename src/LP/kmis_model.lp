\ENCODING=ISO-8859-1
\Problem name: IloCplex

Maximize
 obj1: _elem_0#4 + _elem_3#5 + _elem_4#6 + _elem_1#7 + _elem_2#8
Subject To
 somatorio:         subset_0#0 + subset_1#1 + subset_2#2 + subset_3#3  = 2
 non_neighbors_0_0: subset_0#0 + _elem_0#4 <= 1
 non_neighbors_0_3: subset_0#0 + _elem_3#5 <= 1
 non_neighbors_0_4: subset_0#0 + _elem_4#6 <= 1
 non_neighbors_1_3: subset_1#1 + _elem_3#5 <= 1
 non_neighbors_1_4: subset_1#1 + _elem_4#6 <= 1
 non_neighbors_3_0: subset_3#3 + _elem_0#4 <= 1
 non_neighbors_3_3: subset_3#3 + _elem_3#5 <= 1
Bounds
 0 <= subset_0#0 <= 1
 0 <= subset_1#1 <= 1
 0 <= subset_2#2 <= 1
 0 <= subset_3#3 <= 1
 0 <= _elem_0#4 <= 1
 0 <= _elem_3#5 <= 1
 0 <= _elem_4#6 <= 1
 0 <= _elem_1#7 <= 1
 0 <= _elem_2#8 <= 1
Binaries
 subset_0#0  subset_1#1  subset_2#2  subset_3#3  _elem_0#4  _elem_3#5 
 _elem_4#6  _elem_1#7  _elem_2#8 
End
