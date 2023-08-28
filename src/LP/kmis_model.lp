\ENCODING=ISO-8859-1
\Problem name: IloCplex

Maximize
 obj1: _elem_1#40 + _elem_2#41 + _elem_4#42 + _elem_7#43 + _elem_9#44
       + _elem_13#45 + _elem_14#46 + _elem_16#47 + _elem_17#48 + _elem_18#49
       + _elem_20#50 + _elem_22#51 + _elem_28#52 + _elem_31#53 + _elem_32#54
       + _elem_34#55 + _elem_35#56 + _elem_36#57 + _elem_38#58 + _elem_39#59
       + _elem_5#60 + _elem_11#61 + _elem_15#62 + _elem_27#63 + _elem_30#64
       + _elem_33#65 + _elem_37#66 + _elem_6#67 + _elem_8#68 + _elem_10#69
       + _elem_12#70 + _elem_19#71 + _elem_21#72 + _elem_25#73 + _elem_26#74
       + _elem_29#75 + _elem_3#76 + _elem_23#77 + _elem_24#78 + _elem_0#79
Subject To
 c1:   subset_0#0 + subset_1#1 + subset_2#2 + subset_3#3 + subset_4#4
       + subset_5#5 + subset_6#6 + subset_7#7 + subset_8#8 + subset_9#9
       + subset_10#10 + subset_11#11 + subset_12#12 + subset_13#13
       + subset_14#14 + subset_15#15 + subset_16#16 + subset_17#17
       + subset_18#18 + subset_19#19 + subset_20#20 + subset_21#21
       + subset_22#22 + subset_23#23 + subset_24#24 + subset_25#25
       + subset_26#26 + subset_27#27 + subset_28#28 + subset_29#29
       + subset_30#30 + subset_31#31 + subset_32#32 + subset_33#33
       + subset_34#34 + subset_35#35 + subset_36#36 + subset_37#37
       + subset_38#38 + subset_39#39  = 10
 c2:   subset_0#0 + _elem_1#40 <= 1
 c3:   subset_0#0 + _elem_2#41 <= 1
 c4:   subset_0#0 + _elem_4#42 <= 1
 c5:   subset_0#0 + _elem_7#43 <= 1
 c6:   subset_0#0 + _elem_9#44 <= 1
 c7:   subset_0#0 + _elem_13#45 <= 1
 c8:   subset_0#0 + _elem_14#46 <= 1
 c9:   subset_0#0 + _elem_16#47 <= 1
 c10:  subset_0#0 + _elem_17#48 <= 1
 c11:  subset_0#0 + _elem_18#49 <= 1
 c12:  subset_0#0 + _elem_20#50 <= 1
 c13:  subset_0#0 + _elem_22#51 <= 1
 c14:  subset_0#0 + _elem_28#52 <= 1
 c15:  subset_0#0 + _elem_31#53 <= 1
 c16:  subset_0#0 + _elem_32#54 <= 1
 c17:  subset_0#0 + _elem_34#55 <= 1
 c18:  subset_0#0 + _elem_35#56 <= 1
 c19:  subset_0#0 + _elem_36#57 <= 1
 c20:  subset_0#0 + _elem_38#58 <= 1
 c21:  subset_0#0 + _elem_39#59 <= 1
 c22:  subset_1#1 + _elem_5#60 <= 1
 c23:  subset_1#1 + _elem_7#43 <= 1
 c24:  subset_1#1 + _elem_9#44 <= 1
 c25:  subset_1#1 + _elem_11#61 <= 1
 c26:  subset_1#1 + _elem_14#46 <= 1
 c27:  subset_1#1 + _elem_15#62 <= 1
 c28:  subset_1#1 + _elem_16#47 <= 1
 c29:  subset_1#1 + _elem_18#49 <= 1
 c30:  subset_1#1 + _elem_20#50 <= 1
 c31:  subset_1#1 + _elem_22#51 <= 1
 c32:  subset_1#1 + _elem_27#63 <= 1
 c33:  subset_1#1 + _elem_28#52 <= 1
 c34:  subset_1#1 + _elem_30#64 <= 1
 c35:  subset_1#1 + _elem_33#65 <= 1
 c36:  subset_1#1 + _elem_34#55 <= 1
 c37:  subset_1#1 + _elem_37#66 <= 1
 c38:  subset_1#1 + _elem_39#59 <= 1
 c39:  subset_2#2 + _elem_2#41 <= 1
 c40:  subset_2#2 + _elem_4#42 <= 1
 c41:  subset_2#2 + _elem_5#60 <= 1
 c42:  subset_2#2 + _elem_6#67 <= 1
 c43:  subset_2#2 + _elem_8#68 <= 1
 c44:  subset_2#2 + _elem_9#44 <= 1
 c45:  subset_2#2 + _elem_10#69 <= 1
 c46:  subset_2#2 + _elem_12#70 <= 1
 c47:  subset_2#2 + _elem_15#62 <= 1
 c48:  subset_2#2 + _elem_16#47 <= 1
 c49:  subset_2#2 + _elem_17#48 <= 1
 c50:  subset_2#2 + _elem_18#49 <= 1
 c51:  subset_2#2 + _elem_19#71 <= 1
 c52:  subset_2#2 + _elem_20#50 <= 1
 c53:  subset_2#2 + _elem_21#72 <= 1
 c54:  subset_2#2 + _elem_25#73 <= 1
 c55:  subset_2#2 + _elem_26#74 <= 1
 c56:  subset_2#2 + _elem_27#63 <= 1
 c57:  subset_2#2 + _elem_29#75 <= 1
 c58:  subset_2#2 + _elem_32#54 <= 1
 c59:  subset_2#2 + _elem_33#65 <= 1
 c60:  subset_2#2 + _elem_34#55 <= 1
 c61:  subset_2#2 + _elem_36#57 <= 1
 c62:  subset_2#2 + _elem_37#66 <= 1
 c63:  subset_2#2 + _elem_38#58 <= 1
 c64:  subset_2#2 + _elem_39#59 <= 1
 c65:  subset_3#3 + _elem_1#40 <= 1
 c66:  subset_3#3 + _elem_3#76 <= 1
 c67:  subset_3#3 + _elem_5#60 <= 1
 c68:  subset_3#3 + _elem_8#68 <= 1
 c69:  subset_3#3 + _elem_10#69 <= 1
 c70:  subset_3#3 + _elem_11#61 <= 1
 c71:  subset_3#3 + _elem_12#70 <= 1
 c72:  subset_3#3 + _elem_13#45 <= 1
 c73:  subset_3#3 + _elem_15#62 <= 1
 c74:  subset_3#3 + _elem_16#47 <= 1
 c75:  subset_3#3 + _elem_18#49 <= 1
 c76:  subset_3#3 + _elem_20#50 <= 1
 c77:  subset_3#3 + _elem_22#51 <= 1
 c78:  subset_3#3 + _elem_23#77 <= 1
 c79:  subset_3#3 + _elem_24#78 <= 1
 c80:  subset_3#3 + _elem_25#73 <= 1
 c81:  subset_3#3 + _elem_29#75 <= 1
 c82:  subset_3#3 + _elem_31#53 <= 1
 c83:  subset_3#3 + _elem_32#54 <= 1
 c84:  subset_3#3 + _elem_34#55 <= 1
 c85:  subset_3#3 + _elem_35#56 <= 1
 c86:  subset_3#3 + _elem_37#66 <= 1
 c87:  subset_3#3 + _elem_38#58 <= 1
 c88:  subset_4#4 + _elem_0#79 <= 1
 c89:  subset_4#4 + _elem_1#40 <= 1
 c90:  subset_4#4 + _elem_3#76 <= 1
 c91:  subset_4#4 + _elem_7#43 <= 1
 c92:  subset_4#4 + _elem_8#68 <= 1
 c93:  subset_4#4 + _elem_9#44 <= 1
 c94:  subset_4#4 + _elem_10#69 <= 1
 c95:  subset_4#4 + _elem_12#70 <= 1
 c96:  subset_4#4 + _elem_13#45 <= 1
 c97:  subset_4#4 + _elem_16#47 <= 1
 c98:  subset_4#4 + _elem_17#48 <= 1
 c99:  subset_4#4 + _elem_18#49 <= 1
 c100: subset_4#4 + _elem_19#71 <= 1
 c101: subset_4#4 + _elem_20#50 <= 1
 c102: subset_4#4 + _elem_21#72 <= 1
 c103: subset_4#4 + _elem_22#51 <= 1
 c104: subset_4#4 + _elem_24#78 <= 1
 c105: subset_4#4 + _elem_27#63 <= 1
 c106: subset_4#4 + _elem_32#54 <= 1
 c107: subset_4#4 + _elem_34#55 <= 1
 c108: subset_4#4 + _elem_36#57 <= 1
 c109: subset_4#4 + _elem_37#66 <= 1
 c110: subset_4#4 + _elem_39#59 <= 1
 c111: subset_5#5 + _elem_0#79 <= 1
 c112: subset_5#5 + _elem_1#40 <= 1
 c113: subset_5#5 + _elem_2#41 <= 1
 c114: subset_5#5 + _elem_3#76 <= 1
 c115: subset_5#5 + _elem_4#42 <= 1
 c116: subset_5#5 + _elem_5#60 <= 1
 c117: subset_5#5 + _elem_8#68 <= 1
 c118: subset_5#5 + _elem_11#61 <= 1
 c119: subset_5#5 + _elem_12#70 <= 1
 c120: subset_5#5 + _elem_17#48 <= 1
 c121: subset_5#5 + _elem_18#49 <= 1
 c122: subset_5#5 + _elem_20#50 <= 1
 c123: subset_5#5 + _elem_22#51 <= 1
 c124: subset_5#5 + _elem_24#78 <= 1
 c125: subset_5#5 + _elem_27#63 <= 1
 c126: subset_5#5 + _elem_28#52 <= 1
 c127: subset_5#5 + _elem_31#53 <= 1
 c128: subset_5#5 + _elem_32#54 <= 1
 c129: subset_5#5 + _elem_35#56 <= 1
 c130: subset_5#5 + _elem_38#58 <= 1
 c131: subset_6#6 + _elem_0#79 <= 1
 c132: subset_6#6 + _elem_4#42 <= 1
 c133: subset_6#6 + _elem_6#67 <= 1
 c134: subset_6#6 + _elem_8#68 <= 1
 c135: subset_6#6 + _elem_10#69 <= 1
 c136: subset_6#6 + _elem_12#70 <= 1
 c137: subset_6#6 + _elem_13#45 <= 1
 c138: subset_6#6 + _elem_16#47 <= 1
 c139: subset_6#6 + _elem_21#72 <= 1
 c140: subset_6#6 + _elem_24#78 <= 1
 c141: subset_6#6 + _elem_25#73 <= 1
 c142: subset_6#6 + _elem_28#52 <= 1
 c143: subset_6#6 + _elem_30#64 <= 1
 c144: subset_6#6 + _elem_31#53 <= 1
 c145: subset_6#6 + _elem_33#65 <= 1
 c146: subset_6#6 + _elem_35#56 <= 1
 c147: subset_6#6 + _elem_37#66 <= 1
 c148: subset_6#6 + _elem_38#58 <= 1
 c149: subset_7#7 + _elem_0#79 <= 1
 c150: subset_7#7 + _elem_1#40 <= 1
 c151: subset_7#7 + _elem_5#60 <= 1
 c152: subset_7#7 + _elem_7#43 <= 1
 c153: subset_7#7 + _elem_9#44 <= 1
 c154: subset_7#7 + _elem_12#70 <= 1
 c155: subset_7#7 + _elem_13#45 <= 1
 c156: subset_7#7 + _elem_16#47 <= 1
 c157: subset_7#7 + _elem_19#71 <= 1
 c158: subset_7#7 + _elem_22#51 <= 1
 c159: subset_7#7 + _elem_25#73 <= 1
 c160: subset_7#7 + _elem_26#74 <= 1
 c161: subset_7#7 + _elem_28#52 <= 1
 c162: subset_7#7 + _elem_29#75 <= 1
 c163: subset_7#7 + _elem_30#64 <= 1
 c164: subset_7#7 + _elem_34#55 <= 1
 c165: subset_7#7 + _elem_35#56 <= 1
 c166: subset_7#7 + _elem_36#57 <= 1
 c167: subset_8#8 + _elem_0#79 <= 1
 c168: subset_8#8 + _elem_3#76 <= 1
 c169: subset_8#8 + _elem_4#42 <= 1
 c170: subset_8#8 + _elem_8#68 <= 1
 c171: subset_8#8 + _elem_9#44 <= 1
 c172: subset_8#8 + _elem_10#69 <= 1
 c173: subset_8#8 + _elem_11#61 <= 1
 c174: subset_8#8 + _elem_13#45 <= 1
 c175: subset_8#8 + _elem_16#47 <= 1
 c176: subset_8#8 + _elem_17#48 <= 1
 c177: subset_8#8 + _elem_19#71 <= 1
 c178: subset_8#8 + _elem_21#72 <= 1
 c179: subset_8#8 + _elem_22#51 <= 1
 c180: subset_8#8 + _elem_24#78 <= 1
 c181: subset_8#8 + _elem_29#75 <= 1
 c182: subset_8#8 + _elem_31#53 <= 1
 c183: subset_8#8 + _elem_34#55 <= 1
 c184: subset_8#8 + _elem_35#56 <= 1
 c185: subset_8#8 + _elem_37#66 <= 1
 c186: subset_9#9 + _elem_0#79 <= 1
 c187: subset_9#9 + _elem_3#76 <= 1
 c188: subset_9#9 + _elem_4#42 <= 1
 c189: subset_9#9 + _elem_7#43 <= 1
 c190: subset_9#9 + _elem_8#68 <= 1
 c191: subset_9#9 + _elem_9#44 <= 1
 c192: subset_9#9 + _elem_12#70 <= 1
 c193: subset_9#9 + _elem_13#45 <= 1
 c194: subset_9#9 + _elem_14#46 <= 1
 c195: subset_9#9 + _elem_20#50 <= 1
 c196: subset_9#9 + _elem_22#51 <= 1
 c197: subset_9#9 + _elem_25#73 <= 1
 c198: subset_9#9 + _elem_26#74 <= 1
 c199: subset_9#9 + _elem_28#52 <= 1
 c200: subset_9#9 + _elem_29#75 <= 1
 c201: subset_9#9 + _elem_34#55 <= 1
 c202: subset_9#9 + _elem_36#57 <= 1
 c203: subset_9#9 + _elem_38#58 <= 1
 c204: subset_10#10 + _elem_2#41 <= 1
 c205: subset_10#10 + _elem_4#42 <= 1
 c206: subset_10#10 + _elem_5#60 <= 1
 c207: subset_10#10 + _elem_8#68 <= 1
 c208: subset_10#10 + _elem_11#61 <= 1
 c209: subset_10#10 + _elem_15#62 <= 1
 c210: subset_10#10 + _elem_16#47 <= 1
 c211: subset_10#10 + _elem_17#48 <= 1
 c212: subset_10#10 + _elem_18#49 <= 1
 c213: subset_10#10 + _elem_22#51 <= 1
 c214: subset_10#10 + _elem_23#77 <= 1
 c215: subset_10#10 + _elem_27#63 <= 1
 c216: subset_10#10 + _elem_28#52 <= 1
 c217: subset_10#10 + _elem_29#75 <= 1
 c218: subset_10#10 + _elem_30#64 <= 1
 c219: subset_10#10 + _elem_31#53 <= 1
 c220: subset_10#10 + _elem_32#54 <= 1
 c221: subset_10#10 + _elem_33#65 <= 1
 c222: subset_10#10 + _elem_39#59 <= 1
 c223: subset_11#11 + _elem_8#68 <= 1
 c224: subset_11#11 + _elem_11#61 <= 1
 c225: subset_11#11 + _elem_12#70 <= 1
 c226: subset_11#11 + _elem_15#62 <= 1
 c227: subset_11#11 + _elem_16#47 <= 1
 c228: subset_11#11 + _elem_17#48 <= 1
 c229: subset_11#11 + _elem_18#49 <= 1
 c230: subset_11#11 + _elem_19#71 <= 1
 c231: subset_11#11 + _elem_20#50 <= 1
 c232: subset_11#11 + _elem_21#72 <= 1
 c233: subset_11#11 + _elem_22#51 <= 1
 c234: subset_11#11 + _elem_26#74 <= 1
 c235: subset_11#11 + _elem_27#63 <= 1
 c236: subset_11#11 + _elem_28#52 <= 1
 c237: subset_11#11 + _elem_31#53 <= 1
 c238: subset_11#11 + _elem_36#57 <= 1
 c239: subset_12#12 + _elem_0#79 <= 1
 c240: subset_12#12 + _elem_2#41 <= 1
 c241: subset_12#12 + _elem_6#67 <= 1
 c242: subset_12#12 + _elem_11#61 <= 1
 c243: subset_12#12 + _elem_16#47 <= 1
 c244: subset_12#12 + _elem_18#49 <= 1
 c245: subset_12#12 + _elem_23#77 <= 1
 c246: subset_12#12 + _elem_25#73 <= 1
 c247: subset_12#12 + _elem_26#74 <= 1
 c248: subset_12#12 + _elem_27#63 <= 1
 c249: subset_12#12 + _elem_28#52 <= 1
 c250: subset_12#12 + _elem_37#66 <= 1
 c251: subset_13#13 + _elem_0#79 <= 1
 c252: subset_13#13 + _elem_2#41 <= 1
 c253: subset_13#13 + _elem_3#76 <= 1
 c254: subset_13#13 + _elem_5#60 <= 1
 c255: subset_13#13 + _elem_9#44 <= 1
 c256: subset_13#13 + _elem_10#69 <= 1
 c257: subset_13#13 + _elem_15#62 <= 1
 c258: subset_13#13 + _elem_18#49 <= 1
 c259: subset_13#13 + _elem_19#71 <= 1
 c260: subset_13#13 + _elem_20#50 <= 1
 c261: subset_13#13 + _elem_21#72 <= 1
 c262: subset_13#13 + _elem_23#77 <= 1
 c263: subset_13#13 + _elem_25#73 <= 1
 c264: subset_13#13 + _elem_27#63 <= 1
 c265: subset_13#13 + _elem_30#64 <= 1
 c266: subset_13#13 + _elem_33#65 <= 1
 c267: subset_13#13 + _elem_37#66 <= 1
 c268: subset_14#14 + _elem_0#79 <= 1
 c269: subset_14#14 + _elem_4#42 <= 1
 c270: subset_14#14 + _elem_7#43 <= 1
 c271: subset_14#14 + _elem_9#44 <= 1
 c272: subset_14#14 + _elem_11#61 <= 1
 c273: subset_14#14 + _elem_13#45 <= 1
 c274: subset_14#14 + _elem_14#46 <= 1
 c275: subset_14#14 + _elem_17#48 <= 1
 c276: subset_14#14 + _elem_18#49 <= 1
 c277: subset_14#14 + _elem_20#50 <= 1
 c278: subset_14#14 + _elem_21#72 <= 1
 c279: subset_14#14 + _elem_24#78 <= 1
 c280: subset_14#14 + _elem_28#52 <= 1
 c281: subset_14#14 + _elem_29#75 <= 1
 c282: subset_14#14 + _elem_31#53 <= 1
 c283: subset_14#14 + _elem_33#65 <= 1
 c284: subset_14#14 + _elem_34#55 <= 1
 c285: subset_14#14 + _elem_35#56 <= 1
 c286: subset_14#14 + _elem_36#57 <= 1
 c287: subset_14#14 + _elem_39#59 <= 1
 c288: subset_15#15 + _elem_0#79 <= 1
 c289: subset_15#15 + _elem_1#40 <= 1
 c290: subset_15#15 + _elem_5#60 <= 1
 c291: subset_15#15 + _elem_7#43 <= 1
 c292: subset_15#15 + _elem_14#46 <= 1
 c293: subset_15#15 + _elem_16#47 <= 1
 c294: subset_15#15 + _elem_17#48 <= 1
 c295: subset_15#15 + _elem_18#49 <= 1
 c296: subset_15#15 + _elem_20#50 <= 1
 c297: subset_15#15 + _elem_21#72 <= 1
 c298: subset_15#15 + _elem_22#51 <= 1
 c299: subset_15#15 + _elem_25#73 <= 1
 c300: subset_15#15 + _elem_26#74 <= 1
 c301: subset_15#15 + _elem_27#63 <= 1
 c302: subset_15#15 + _elem_28#52 <= 1
 c303: subset_15#15 + _elem_29#75 <= 1
 c304: subset_15#15 + _elem_31#53 <= 1
 c305: subset_15#15 + _elem_33#65 <= 1
 c306: subset_15#15 + _elem_34#55 <= 1
 c307: subset_15#15 + _elem_35#56 <= 1
 c308: subset_15#15 + _elem_37#66 <= 1
 c309: subset_15#15 + _elem_39#59 <= 1
 c310: subset_16#16 + _elem_4#42 <= 1
 c311: subset_16#16 + _elem_6#67 <= 1
 c312: subset_16#16 + _elem_8#68 <= 1
 c313: subset_16#16 + _elem_10#69 <= 1
 c314: subset_16#16 + _elem_12#70 <= 1
 c315: subset_16#16 + _elem_13#45 <= 1
 c316: subset_16#16 + _elem_14#46 <= 1
 c317: subset_16#16 + _elem_15#62 <= 1
 c318: subset_16#16 + _elem_16#47 <= 1
 c319: subset_16#16 + _elem_18#49 <= 1
 c320: subset_16#16 + _elem_19#71 <= 1
 c321: subset_16#16 + _elem_20#50 <= 1
 c322: subset_16#16 + _elem_22#51 <= 1
 c323: subset_16#16 + _elem_23#77 <= 1
 c324: subset_16#16 + _elem_24#78 <= 1
 c325: subset_16#16 + _elem_25#73 <= 1
 c326: subset_16#16 + _elem_26#74 <= 1
 c327: subset_16#16 + _elem_27#63 <= 1
 c328: subset_16#16 + _elem_32#54 <= 1
 c329: subset_16#16 + _elem_33#65 <= 1
 c330: subset_16#16 + _elem_34#55 <= 1
 c331: subset_16#16 + _elem_38#58 <= 1
 c332: subset_16#16 + _elem_39#59 <= 1
 c333: subset_17#17 + _elem_0#79 <= 1
 c334: subset_17#17 + _elem_2#41 <= 1
 c335: subset_17#17 + _elem_5#60 <= 1
 c336: subset_17#17 + _elem_8#68 <= 1
 c337: subset_17#17 + _elem_10#69 <= 1
 c338: subset_17#17 + _elem_11#61 <= 1
 c339: subset_17#17 + _elem_12#70 <= 1
 c340: subset_17#17 + _elem_13#45 <= 1
 c341: subset_17#17 + _elem_17#48 <= 1
 c342: subset_17#17 + _elem_19#71 <= 1
 c343: subset_17#17 + _elem_22#51 <= 1
 c344: subset_17#17 + _elem_26#74 <= 1
 c345: subset_17#17 + _elem_27#63 <= 1
 c346: subset_17#17 + _elem_28#52 <= 1
 c347: subset_17#17 + _elem_29#75 <= 1
 c348: subset_17#17 + _elem_30#64 <= 1
 c349: subset_17#17 + _elem_33#65 <= 1
 c350: subset_17#17 + _elem_34#55 <= 1
 c351: subset_17#17 + _elem_38#58 <= 1
 c352: subset_17#17 + _elem_39#59 <= 1
 c353: subset_18#18 + _elem_5#60 <= 1
 c354: subset_18#18 + _elem_8#68 <= 1
 c355: subset_18#18 + _elem_14#46 <= 1
 c356: subset_18#18 + _elem_16#47 <= 1
 c357: subset_18#18 + _elem_17#48 <= 1
 c358: subset_18#18 + _elem_19#71 <= 1
 c359: subset_18#18 + _elem_22#51 <= 1
 c360: subset_18#18 + _elem_24#78 <= 1
 c361: subset_18#18 + _elem_26#74 <= 1
 c362: subset_18#18 + _elem_27#63 <= 1
 c363: subset_18#18 + _elem_28#52 <= 1
 c364: subset_18#18 + _elem_29#75 <= 1
 c365: subset_18#18 + _elem_30#64 <= 1
 c366: subset_18#18 + _elem_31#53 <= 1
 c367: subset_18#18 + _elem_32#54 <= 1
 c368: subset_18#18 + _elem_37#66 <= 1
 c369: subset_18#18 + _elem_38#58 <= 1
 c370: subset_19#19 + _elem_1#40 <= 1
 c371: subset_19#19 + _elem_5#60 <= 1
 c372: subset_19#19 + _elem_6#67 <= 1
 c373: subset_19#19 + _elem_7#43 <= 1
 c374: subset_19#19 + _elem_8#68 <= 1
 c375: subset_19#19 + _elem_10#69 <= 1
 c376: subset_19#19 + _elem_11#61 <= 1
 c377: subset_19#19 + _elem_12#70 <= 1
 c378: subset_19#19 + _elem_16#47 <= 1
 c379: subset_19#19 + _elem_17#48 <= 1
 c380: subset_19#19 + _elem_19#71 <= 1
 c381: subset_19#19 + _elem_23#77 <= 1
 c382: subset_19#19 + _elem_24#78 <= 1
 c383: subset_19#19 + _elem_30#64 <= 1
 c384: subset_19#19 + _elem_31#53 <= 1
 c385: subset_19#19 + _elem_33#65 <= 1
 c386: subset_19#19 + _elem_35#56 <= 1
 c387: subset_19#19 + _elem_38#58 <= 1
 c388: subset_20#20 + _elem_0#79 <= 1
 c389: subset_20#20 + _elem_2#41 <= 1
 c390: subset_20#20 + _elem_3#76 <= 1
 c391: subset_20#20 + _elem_7#43 <= 1
 c392: subset_20#20 + _elem_9#44 <= 1
 c393: subset_20#20 + _elem_11#61 <= 1
 c394: subset_20#20 + _elem_12#70 <= 1
 c395: subset_20#20 + _elem_14#46 <= 1
 c396: subset_20#20 + _elem_17#48 <= 1
 c397: subset_20#20 + _elem_18#49 <= 1
 c398: subset_20#20 + _elem_22#51 <= 1
 c399: subset_20#20 + _elem_24#78 <= 1
 c400: subset_20#20 + _elem_25#73 <= 1
 c401: subset_20#20 + _elem_26#74 <= 1
 c402: subset_20#20 + _elem_28#52 <= 1
 c403: subset_20#20 + _elem_30#64 <= 1
 c404: subset_20#20 + _elem_31#53 <= 1
 c405: subset_20#20 + _elem_32#54 <= 1
 c406: subset_20#20 + _elem_35#56 <= 1
 c407: subset_20#20 + _elem_37#66 <= 1
 c408: subset_20#20 + _elem_38#58 <= 1
 c409: subset_21#21 + _elem_0#79 <= 1
 c410: subset_21#21 + _elem_3#76 <= 1
 c411: subset_21#21 + _elem_4#42 <= 1
 c412: subset_21#21 + _elem_8#68 <= 1
 c413: subset_21#21 + _elem_11#61 <= 1
 c414: subset_21#21 + _elem_14#46 <= 1
 c415: subset_21#21 + _elem_15#62 <= 1
 c416: subset_21#21 + _elem_16#47 <= 1
 c417: subset_21#21 + _elem_18#49 <= 1
 c418: subset_21#21 + _elem_19#71 <= 1
 c419: subset_21#21 + _elem_28#52 <= 1
 c420: subset_21#21 + _elem_34#55 <= 1
 c421: subset_21#21 + _elem_37#66 <= 1
 c422: subset_22#22 + _elem_0#79 <= 1
 c423: subset_22#22 + _elem_3#76 <= 1
 c424: subset_22#22 + _elem_6#67 <= 1
 c425: subset_22#22 + _elem_8#68 <= 1
 c426: subset_22#22 + _elem_10#69 <= 1
 c427: subset_22#22 + _elem_13#45 <= 1
 c428: subset_22#22 + _elem_14#46 <= 1
 c429: subset_22#22 + _elem_16#47 <= 1
 c430: subset_22#22 + _elem_17#48 <= 1
 c431: subset_22#22 + _elem_19#71 <= 1
 c432: subset_22#22 + _elem_21#72 <= 1
 c433: subset_22#22 + _elem_23#77 <= 1
 c434: subset_22#22 + _elem_24#78 <= 1
 c435: subset_22#22 + _elem_25#73 <= 1
 c436: subset_22#22 + _elem_26#74 <= 1
 c437: subset_22#22 + _elem_28#52 <= 1
 c438: subset_22#22 + _elem_29#75 <= 1
 c439: subset_22#22 + _elem_32#54 <= 1
 c440: subset_22#22 + _elem_33#65 <= 1
 c441: subset_22#22 + _elem_34#55 <= 1
 c442: subset_22#22 + _elem_35#56 <= 1
 c443: subset_22#22 + _elem_36#57 <= 1
 c444: subset_23#23 + _elem_1#40 <= 1
 c445: subset_23#23 + _elem_3#76 <= 1
 c446: subset_23#23 + _elem_4#42 <= 1
 c447: subset_23#23 + _elem_5#60 <= 1
 c448: subset_23#23 + _elem_6#67 <= 1
 c449: subset_23#23 + _elem_9#44 <= 1
 c450: subset_23#23 + _elem_11#61 <= 1
 c451: subset_23#23 + _elem_13#45 <= 1
 c452: subset_23#23 + _elem_16#47 <= 1
 c453: subset_23#23 + _elem_18#49 <= 1
 c454: subset_23#23 + _elem_19#71 <= 1
 c455: subset_23#23 + _elem_22#51 <= 1
 c456: subset_23#23 + _elem_23#77 <= 1
 c457: subset_23#23 + _elem_24#78 <= 1
 c458: subset_23#23 + _elem_28#52 <= 1
 c459: subset_23#23 + _elem_30#64 <= 1
 c460: subset_23#23 + _elem_31#53 <= 1
 c461: subset_23#23 + _elem_32#54 <= 1
 c462: subset_23#23 + _elem_36#57 <= 1
 c463: subset_23#23 + _elem_37#66 <= 1
 c464: subset_24#24 + _elem_2#41 <= 1
 c465: subset_24#24 + _elem_5#60 <= 1
 c466: subset_24#24 + _elem_11#61 <= 1
 c467: subset_24#24 + _elem_12#70 <= 1
 c468: subset_24#24 + _elem_13#45 <= 1
 c469: subset_24#24 + _elem_15#62 <= 1
 c470: subset_24#24 + _elem_16#47 <= 1
 c471: subset_24#24 + _elem_21#72 <= 1
 c472: subset_24#24 + _elem_23#77 <= 1
 c473: subset_24#24 + _elem_26#74 <= 1
 c474: subset_24#24 + _elem_28#52 <= 1
 c475: subset_24#24 + _elem_30#64 <= 1
 c476: subset_24#24 + _elem_32#54 <= 1
 c477: subset_24#24 + _elem_35#56 <= 1
 c478: subset_24#24 + _elem_36#57 <= 1
 c479: subset_24#24 + _elem_39#59 <= 1
 c480: subset_25#25 + _elem_3#76 <= 1
 c481: subset_25#25 + _elem_4#42 <= 1
 c482: subset_25#25 + _elem_5#60 <= 1
 c483: subset_25#25 + _elem_6#67 <= 1
 c484: subset_25#25 + _elem_10#69 <= 1
 c485: subset_25#25 + _elem_11#61 <= 1
 c486: subset_25#25 + _elem_14#46 <= 1
 c487: subset_25#25 + _elem_17#48 <= 1
 c488: subset_25#25 + _elem_18#49 <= 1
 c489: subset_25#25 + _elem_20#50 <= 1
 c490: subset_25#25 + _elem_21#72 <= 1
 c491: subset_25#25 + _elem_22#51 <= 1
 c492: subset_25#25 + _elem_23#77 <= 1
 c493: subset_25#25 + _elem_24#78 <= 1
 c494: subset_25#25 + _elem_25#73 <= 1
 c495: subset_25#25 + _elem_30#64 <= 1
 c496: subset_25#25 + _elem_31#53 <= 1
 c497: subset_25#25 + _elem_32#54 <= 1
 c498: subset_25#25 + _elem_33#65 <= 1
 c499: subset_25#25 + _elem_36#57 <= 1
 c500: subset_25#25 + _elem_38#58 <= 1
 c501: subset_26#26 + _elem_0#79 <= 1
 c502: subset_26#26 + _elem_1#40 <= 1
 c503: subset_26#26 + _elem_2#41 <= 1
 c504: subset_26#26 + _elem_3#76 <= 1
 c505: subset_26#26 + _elem_4#42 <= 1
 c506: subset_26#26 + _elem_8#68 <= 1
 c507: subset_26#26 + _elem_12#70 <= 1
 c508: subset_26#26 + _elem_15#62 <= 1
 c509: subset_26#26 + _elem_16#47 <= 1
 c510: subset_26#26 + _elem_17#48 <= 1
 c511: subset_26#26 + _elem_21#72 <= 1
 c512: subset_26#26 + _elem_24#78 <= 1
 c513: subset_26#26 + _elem_25#73 <= 1
 c514: subset_26#26 + _elem_30#64 <= 1
 c515: subset_26#26 + _elem_31#53 <= 1
 c516: subset_26#26 + _elem_33#65 <= 1
 c517: subset_26#26 + _elem_34#55 <= 1
 c518: subset_26#26 + _elem_35#56 <= 1
 c519: subset_26#26 + _elem_36#57 <= 1
 c520: subset_26#26 + _elem_38#58 <= 1
 c521: subset_26#26 + _elem_39#59 <= 1
 c522: subset_27#27 + _elem_0#79 <= 1
 c523: subset_27#27 + _elem_1#40 <= 1
 c524: subset_27#27 + _elem_2#41 <= 1
 c525: subset_27#27 + _elem_3#76 <= 1
 c526: subset_27#27 + _elem_5#60 <= 1
 c527: subset_27#27 + _elem_7#43 <= 1
 c528: subset_27#27 + _elem_8#68 <= 1
 c529: subset_27#27 + _elem_9#44 <= 1
 c530: subset_27#27 + _elem_12#70 <= 1
 c531: subset_27#27 + _elem_13#45 <= 1
 c532: subset_27#27 + _elem_14#46 <= 1
 c533: subset_27#27 + _elem_15#62 <= 1
 c534: subset_27#27 + _elem_16#47 <= 1
 c535: subset_27#27 + _elem_17#48 <= 1
 c536: subset_27#27 + _elem_18#49 <= 1
 c537: subset_27#27 + _elem_23#77 <= 1
 c538: subset_27#27 + _elem_24#78 <= 1
 c539: subset_27#27 + _elem_26#74 <= 1
 c540: subset_27#27 + _elem_27#63 <= 1
 c541: subset_27#27 + _elem_28#52 <= 1
 c542: subset_27#27 + _elem_29#75 <= 1
 c543: subset_27#27 + _elem_31#53 <= 1
 c544: subset_27#27 + _elem_35#56 <= 1
 c545: subset_27#27 + _elem_36#57 <= 1
 c546: subset_27#27 + _elem_37#66 <= 1
 c547: subset_27#27 + _elem_38#58 <= 1
 c548: subset_27#27 + _elem_39#59 <= 1
 c549: subset_28#28 + _elem_1#40 <= 1
 c550: subset_28#28 + _elem_2#41 <= 1
 c551: subset_28#28 + _elem_3#76 <= 1
 c552: subset_28#28 + _elem_8#68 <= 1
 c553: subset_28#28 + _elem_10#69 <= 1
 c554: subset_28#28 + _elem_15#62 <= 1
 c555: subset_28#28 + _elem_16#47 <= 1
 c556: subset_28#28 + _elem_26#74 <= 1
 c557: subset_28#28 + _elem_27#63 <= 1
 c558: subset_28#28 + _elem_30#64 <= 1
 c559: subset_28#28 + _elem_32#54 <= 1
 c560: subset_28#28 + _elem_33#65 <= 1
 c561: subset_28#28 + _elem_37#66 <= 1
 c562: subset_29#29 + _elem_0#79 <= 1
 c563: subset_29#29 + _elem_2#41 <= 1
 c564: subset_29#29 + _elem_5#60 <= 1
 c565: subset_29#29 + _elem_6#67 <= 1
 c566: subset_29#29 + _elem_10#69 <= 1
 c567: subset_29#29 + _elem_11#61 <= 1
 c568: subset_29#29 + _elem_12#70 <= 1
 c569: subset_29#29 + _elem_16#47 <= 1
 c570: subset_29#29 + _elem_19#71 <= 1
 c571: subset_29#29 + _elem_20#50 <= 1
 c572: subset_29#29 + _elem_22#51 <= 1
 c573: subset_29#29 + _elem_26#74 <= 1
 c574: subset_29#29 + _elem_27#63 <= 1
 c575: subset_29#29 + _elem_28#52 <= 1
 c576: subset_29#29 + _elem_30#64 <= 1
 c577: subset_29#29 + _elem_31#53 <= 1
 c578: subset_29#29 + _elem_32#54 <= 1
 c579: subset_29#29 + _elem_35#56 <= 1
 c580: subset_29#29 + _elem_36#57 <= 1
 c581: subset_29#29 + _elem_37#66 <= 1
 c582: subset_29#29 + _elem_39#59 <= 1
 c583: subset_30#30 + _elem_0#79 <= 1
 c584: subset_30#30 + _elem_1#40 <= 1
 c585: subset_30#30 + _elem_6#67 <= 1
 c586: subset_30#30 + _elem_7#43 <= 1
 c587: subset_30#30 + _elem_8#68 <= 1
 c588: subset_30#30 + _elem_9#44 <= 1
 c589: subset_30#30 + _elem_10#69 <= 1
 c590: subset_30#30 + _elem_15#62 <= 1
 c591: subset_30#30 + _elem_17#48 <= 1
 c592: subset_30#30 + _elem_19#71 <= 1
 c593: subset_30#30 + _elem_21#72 <= 1
 c594: subset_30#30 + _elem_23#77 <= 1
 c595: subset_30#30 + _elem_24#78 <= 1
 c596: subset_30#30 + _elem_26#74 <= 1
 c597: subset_30#30 + _elem_28#52 <= 1
 c598: subset_30#30 + _elem_29#75 <= 1
 c599: subset_30#30 + _elem_30#64 <= 1
 c600: subset_30#30 + _elem_35#56 <= 1
 c601: subset_30#30 + _elem_37#66 <= 1
 c602: subset_31#31 + _elem_0#79 <= 1
 c603: subset_31#31 + _elem_3#76 <= 1
 c604: subset_31#31 + _elem_4#42 <= 1
 c605: subset_31#31 + _elem_6#67 <= 1
 c606: subset_31#31 + _elem_8#68 <= 1
 c607: subset_31#31 + _elem_9#44 <= 1
 c608: subset_31#31 + _elem_10#69 <= 1
 c609: subset_31#31 + _elem_13#45 <= 1
 c610: subset_31#31 + _elem_14#46 <= 1
 c611: subset_31#31 + _elem_15#62 <= 1
 c612: subset_31#31 + _elem_16#47 <= 1
 c613: subset_31#31 + _elem_21#72 <= 1
 c614: subset_31#31 + _elem_26#74 <= 1
 c615: subset_31#31 + _elem_28#52 <= 1
 c616: subset_31#31 + _elem_30#64 <= 1
 c617: subset_31#31 + _elem_32#54 <= 1
 c618: subset_31#31 + _elem_36#57 <= 1
 c619: subset_31#31 + _elem_38#58 <= 1
 c620: subset_31#31 + _elem_39#59 <= 1
 c621: subset_32#32 + _elem_1#40 <= 1
 c622: subset_32#32 + _elem_2#41 <= 1
 c623: subset_32#32 + _elem_5#60 <= 1
 c624: subset_32#32 + _elem_7#43 <= 1
 c625: subset_32#32 + _elem_9#44 <= 1
 c626: subset_32#32 + _elem_11#61 <= 1
 c627: subset_32#32 + _elem_12#70 <= 1
 c628: subset_32#32 + _elem_15#62 <= 1
 c629: subset_32#32 + _elem_17#48 <= 1
 c630: subset_32#32 + _elem_18#49 <= 1
 c631: subset_32#32 + _elem_19#71 <= 1
 c632: subset_32#32 + _elem_22#51 <= 1
 c633: subset_32#32 + _elem_23#77 <= 1
 c634: subset_32#32 + _elem_24#78 <= 1
 c635: subset_32#32 + _elem_26#74 <= 1
 c636: subset_32#32 + _elem_27#63 <= 1
 c637: subset_32#32 + _elem_28#52 <= 1
 c638: subset_32#32 + _elem_33#65 <= 1
 c639: subset_32#32 + _elem_36#57 <= 1
 c640: subset_32#32 + _elem_39#59 <= 1
 c641: subset_33#33 + _elem_0#79 <= 1
 c642: subset_33#33 + _elem_1#40 <= 1
 c643: subset_33#33 + _elem_3#76 <= 1
 c644: subset_33#33 + _elem_4#42 <= 1
 c645: subset_33#33 + _elem_5#60 <= 1
 c646: subset_33#33 + _elem_7#43 <= 1
 c647: subset_33#33 + _elem_9#44 <= 1
 c648: subset_33#33 + _elem_10#69 <= 1
 c649: subset_33#33 + _elem_12#70 <= 1
 c650: subset_33#33 + _elem_13#45 <= 1
 c651: subset_33#33 + _elem_14#46 <= 1
 c652: subset_33#33 + _elem_18#49 <= 1
 c653: subset_33#33 + _elem_20#50 <= 1
 c654: subset_33#33 + _elem_22#51 <= 1
 c655: subset_33#33 + _elem_23#77 <= 1
 c656: subset_33#33 + _elem_24#78 <= 1
 c657: subset_33#33 + _elem_25#73 <= 1
 c658: subset_33#33 + _elem_27#63 <= 1
 c659: subset_33#33 + _elem_28#52 <= 1
 c660: subset_33#33 + _elem_31#53 <= 1
 c661: subset_33#33 + _elem_32#54 <= 1
 c662: subset_33#33 + _elem_33#65 <= 1
 c663: subset_33#33 + _elem_34#55 <= 1
 c664: subset_33#33 + _elem_35#56 <= 1
 c665: subset_33#33 + _elem_39#59 <= 1
 c666: subset_34#34 + _elem_2#41 <= 1
 c667: subset_34#34 + _elem_3#76 <= 1
 c668: subset_34#34 + _elem_4#42 <= 1
 c669: subset_34#34 + _elem_6#67 <= 1
 c670: subset_34#34 + _elem_9#44 <= 1
 c671: subset_34#34 + _elem_10#69 <= 1
 c672: subset_34#34 + _elem_13#45 <= 1
 c673: subset_34#34 + _elem_14#46 <= 1
 c674: subset_34#34 + _elem_15#62 <= 1
 c675: subset_34#34 + _elem_16#47 <= 1
 c676: subset_34#34 + _elem_19#71 <= 1
 c677: subset_34#34 + _elem_21#72 <= 1
 c678: subset_34#34 + _elem_24#78 <= 1
 c679: subset_34#34 + _elem_26#74 <= 1
 c680: subset_34#34 + _elem_27#63 <= 1
 c681: subset_34#34 + _elem_30#64 <= 1
 c682: subset_34#34 + _elem_32#54 <= 1
 c683: subset_34#34 + _elem_36#57 <= 1
 c684: subset_34#34 + _elem_38#58 <= 1
 c685: subset_34#34 + _elem_39#59 <= 1
 c686: subset_35#35 + _elem_0#79 <= 1
 c687: subset_35#35 + _elem_2#41 <= 1
 c688: subset_35#35 + _elem_3#76 <= 1
 c689: subset_35#35 + _elem_9#44 <= 1
 c690: subset_35#35 + _elem_10#69 <= 1
 c691: subset_35#35 + _elem_11#61 <= 1
 c692: subset_35#35 + _elem_12#70 <= 1
 c693: subset_35#35 + _elem_13#45 <= 1
 c694: subset_35#35 + _elem_14#46 <= 1
 c695: subset_35#35 + _elem_16#47 <= 1
 c696: subset_35#35 + _elem_23#77 <= 1
 c697: subset_35#35 + _elem_24#78 <= 1
 c698: subset_35#35 + _elem_25#73 <= 1
 c699: subset_35#35 + _elem_28#52 <= 1
 c700: subset_35#35 + _elem_29#75 <= 1
 c701: subset_35#35 + _elem_30#64 <= 1
 c702: subset_35#35 + _elem_33#65 <= 1
 c703: subset_35#35 + _elem_34#55 <= 1
 c704: subset_35#35 + _elem_36#57 <= 1
 c705: subset_35#35 + _elem_37#66 <= 1
 c706: subset_36#36 + _elem_1#40 <= 1
 c707: subset_36#36 + _elem_2#41 <= 1
 c708: subset_36#36 + _elem_9#44 <= 1
 c709: subset_36#36 + _elem_12#70 <= 1
 c710: subset_36#36 + _elem_13#45 <= 1
 c711: subset_36#36 + _elem_16#47 <= 1
 c712: subset_36#36 + _elem_17#48 <= 1
 c713: subset_36#36 + _elem_22#51 <= 1
 c714: subset_36#36 + _elem_23#77 <= 1
 c715: subset_36#36 + _elem_24#78 <= 1
 c716: subset_36#36 + _elem_25#73 <= 1
 c717: subset_36#36 + _elem_27#63 <= 1
 c718: subset_36#36 + _elem_30#64 <= 1
 c719: subset_36#36 + _elem_36#57 <= 1
 c720: subset_36#36 + _elem_37#66 <= 1
 c721: subset_36#36 + _elem_39#59 <= 1
 c722: subset_37#37 + _elem_2#41 <= 1
 c723: subset_37#37 + _elem_7#43 <= 1
 c724: subset_37#37 + _elem_9#44 <= 1
 c725: subset_37#37 + _elem_10#69 <= 1
 c726: subset_37#37 + _elem_11#61 <= 1
 c727: subset_37#37 + _elem_15#62 <= 1
 c728: subset_37#37 + _elem_18#49 <= 1
 c729: subset_37#37 + _elem_22#51 <= 1
 c730: subset_37#37 + _elem_25#73 <= 1
 c731: subset_37#37 + _elem_26#74 <= 1
 c732: subset_37#37 + _elem_27#63 <= 1
 c733: subset_37#37 + _elem_31#53 <= 1
 c734: subset_37#37 + _elem_32#54 <= 1
 c735: subset_37#37 + _elem_33#65 <= 1
 c736: subset_37#37 + _elem_34#55 <= 1
 c737: subset_37#37 + _elem_35#56 <= 1
 c738: subset_37#37 + _elem_39#59 <= 1
 c739: subset_38#38 + _elem_0#79 <= 1
 c740: subset_38#38 + _elem_1#40 <= 1
 c741: subset_38#38 + _elem_2#41 <= 1
 c742: subset_38#38 + _elem_4#42 <= 1
 c743: subset_38#38 + _elem_5#60 <= 1
 c744: subset_38#38 + _elem_6#67 <= 1
 c745: subset_38#38 + _elem_8#68 <= 1
 c746: subset_38#38 + _elem_10#69 <= 1
 c747: subset_38#38 + _elem_11#61 <= 1
 c748: subset_38#38 + _elem_12#70 <= 1
 c749: subset_38#38 + _elem_13#45 <= 1
 c750: subset_38#38 + _elem_16#47 <= 1
 c751: subset_38#38 + _elem_17#48 <= 1
 c752: subset_38#38 + _elem_19#71 <= 1
 c753: subset_38#38 + _elem_20#50 <= 1
 c754: subset_38#38 + _elem_21#72 <= 1
 c755: subset_38#38 + _elem_22#51 <= 1
 c756: subset_38#38 + _elem_23#77 <= 1
 c757: subset_38#38 + _elem_24#78 <= 1
 c758: subset_38#38 + _elem_25#73 <= 1
 c759: subset_38#38 + _elem_26#74 <= 1
 c760: subset_38#38 + _elem_27#63 <= 1
 c761: subset_38#38 + _elem_29#75 <= 1
 c762: subset_38#38 + _elem_32#54 <= 1
 c763: subset_38#38 + _elem_34#55 <= 1
 c764: subset_38#38 + _elem_35#56 <= 1
 c765: subset_38#38 + _elem_37#66 <= 1
 c766: subset_38#38 + _elem_39#59 <= 1
 c767: subset_39#39 + _elem_2#41 <= 1
 c768: subset_39#39 + _elem_3#76 <= 1
 c769: subset_39#39 + _elem_4#42 <= 1
 c770: subset_39#39 + _elem_5#60 <= 1
 c771: subset_39#39 + _elem_6#67 <= 1
 c772: subset_39#39 + _elem_7#43 <= 1
 c773: subset_39#39 + _elem_8#68 <= 1
 c774: subset_39#39 + _elem_13#45 <= 1
 c775: subset_39#39 + _elem_15#62 <= 1
 c776: subset_39#39 + _elem_16#47 <= 1
 c777: subset_39#39 + _elem_19#71 <= 1
 c778: subset_39#39 + _elem_21#72 <= 1
 c779: subset_39#39 + _elem_23#77 <= 1
 c780: subset_39#39 + _elem_26#74 <= 1
 c781: subset_39#39 + _elem_30#64 <= 1
 c782: subset_39#39 + _elem_33#65 <= 1
 c783: subset_39#39 + _elem_34#55 <= 1
 c784: subset_39#39 + _elem_37#66 <= 1
 c785: subset_39#39 + _elem_38#58 <= 1
 c786: subset_39#39 + _elem_39#59 <= 1
Bounds
 0 <= subset_0#0 <= 1
 0 <= subset_1#1 <= 1
 0 <= subset_2#2 <= 1
 0 <= subset_3#3 <= 1
 0 <= subset_4#4 <= 1
 0 <= subset_5#5 <= 1
 0 <= subset_6#6 <= 1
 0 <= subset_7#7 <= 1
 0 <= subset_8#8 <= 1
 0 <= subset_9#9 <= 1
 0 <= subset_10#10 <= 1
 0 <= subset_11#11 <= 1
 0 <= subset_12#12 <= 1
 0 <= subset_13#13 <= 1
 0 <= subset_14#14 <= 1
 0 <= subset_15#15 <= 1
 0 <= subset_16#16 <= 1
 0 <= subset_17#17 <= 1
 0 <= subset_18#18 <= 1
 0 <= subset_19#19 <= 1
 0 <= subset_20#20 <= 1
 0 <= subset_21#21 <= 1
 0 <= subset_22#22 <= 1
 0 <= subset_23#23 <= 1
 0 <= subset_24#24 <= 1
 0 <= subset_25#25 <= 1
 0 <= subset_26#26 <= 1
 0 <= subset_27#27 <= 1
 0 <= subset_28#28 <= 1
 0 <= subset_29#29 <= 1
 0 <= subset_30#30 <= 1
 0 <= subset_31#31 <= 1
 0 <= subset_32#32 <= 1
 0 <= subset_33#33 <= 1
 0 <= subset_34#34 <= 1
 0 <= subset_35#35 <= 1
 0 <= subset_36#36 <= 1
 0 <= subset_37#37 <= 1
 0 <= subset_38#38 <= 1
 0 <= subset_39#39 <= 1
 0 <= _elem_1#40 <= 1
 0 <= _elem_2#41 <= 1
 0 <= _elem_4#42 <= 1
 0 <= _elem_7#43 <= 1
 0 <= _elem_9#44 <= 1
 0 <= _elem_13#45 <= 1
 0 <= _elem_14#46 <= 1
 0 <= _elem_16#47 <= 1
 0 <= _elem_17#48 <= 1
 0 <= _elem_18#49 <= 1
 0 <= _elem_20#50 <= 1
 0 <= _elem_22#51 <= 1
 0 <= _elem_28#52 <= 1
 0 <= _elem_31#53 <= 1
 0 <= _elem_32#54 <= 1
 0 <= _elem_34#55 <= 1
 0 <= _elem_35#56 <= 1
 0 <= _elem_36#57 <= 1
 0 <= _elem_38#58 <= 1
 0 <= _elem_39#59 <= 1
 0 <= _elem_5#60 <= 1
 0 <= _elem_11#61 <= 1
 0 <= _elem_15#62 <= 1
 0 <= _elem_27#63 <= 1
 0 <= _elem_30#64 <= 1
 0 <= _elem_33#65 <= 1
 0 <= _elem_37#66 <= 1
 0 <= _elem_6#67 <= 1
 0 <= _elem_8#68 <= 1
 0 <= _elem_10#69 <= 1
 0 <= _elem_12#70 <= 1
 0 <= _elem_19#71 <= 1
 0 <= _elem_21#72 <= 1
 0 <= _elem_25#73 <= 1
 0 <= _elem_26#74 <= 1
 0 <= _elem_29#75 <= 1
 0 <= _elem_3#76 <= 1
 0 <= _elem_23#77 <= 1
 0 <= _elem_24#78 <= 1
 0 <= _elem_0#79 <= 1
Binaries
 subset_0#0  subset_1#1  subset_2#2  subset_3#3  subset_4#4  subset_5#5 
 subset_6#6  subset_7#7  subset_8#8  subset_9#9  subset_10#10  subset_11#11 
 subset_12#12  subset_13#13  subset_14#14  subset_15#15  subset_16#16 
 subset_17#17  subset_18#18  subset_19#19  subset_20#20  subset_21#21 
 subset_22#22  subset_23#23  subset_24#24  subset_25#25  subset_26#26 
 subset_27#27  subset_28#28  subset_29#29  subset_30#30  subset_31#31 
 subset_32#32  subset_33#33  subset_34#34  subset_35#35  subset_36#36 
 subset_37#37  subset_38#38  subset_39#39  _elem_1#40  _elem_2#41  _elem_4#42 
 _elem_7#43  _elem_9#44  _elem_13#45  _elem_14#46  _elem_16#47  _elem_17#48 
 _elem_18#49  _elem_20#50  _elem_22#51  _elem_28#52  _elem_31#53  _elem_32#54 
 _elem_34#55  _elem_35#56  _elem_36#57  _elem_38#58  _elem_39#59  _elem_5#60 
 _elem_11#61  _elem_15#62  _elem_27#63  _elem_30#64  _elem_33#65  _elem_37#66 
 _elem_6#67  _elem_8#68  _elem_10#69  _elem_12#70  _elem_19#71  _elem_21#72 
 _elem_25#73  _elem_26#74  _elem_29#75  _elem_3#76  _elem_23#77  _elem_24#78 
 _elem_0#79 
End
