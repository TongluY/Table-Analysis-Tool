CC=g++
CFLAGS=-fPIC -Wall -Wextra -O2
LDFLAGS=-shared
RM=rm -f
TARGET_LIB=libsparrow.so
P1_TARGET=p1
P1_TEST=test1_build test2_bitcounter test3_overload test4_bit_and test5_p1_program
P2_TARGET=p2
P2_TEST=test6_struct test7_dropzero test8_average test9_divide test10_p2_program
P3_TARGET=p3
P3_TEST=test11_ref test12_const test13_parse test14_dblptr test15_p3_program
P4_TARGET=p4
P4_TEST=test16_constructor test17_cout test18_methods test19_indexing test20_p4_program
P5_TARGET=p5
P5_TEST=test21_destructor test22_cp_constructor test23_cp_assignment test24_mv_constructor test25_mv_assignment
P6_TARGET=p6
P6_TEST=test26_add_col test27_get_col test28_output test29_files test30_division

all: $(TARGET_LIB) $(P1_TARGET) $(P2_TARGET) $(P3_TARGET) $(P4_TARGET) 
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

$(P1_TARGET): $(P1_TARGET).o $(TARGET_LIB)
	$(CC) $(P1_TARGET).o -L. -lsparrow -o $(P1_TARGET)

$(P1_TARGET).o: $(P1_TARGET).cpp sparrow.h
	$(CC) $(CFLAGS) -c $(P1_TARGET).cpp

$(P2_TARGET): $(P2_TARGET).o $(TARGET_LIB)
	$(CC) $(P2_TARGET).o -L. -lsparrow -o $(P2_TARGET)

$(P2_TARGET).o: $(P2_TARGET).cpp sparrow.h
	$(CC) $(CFLAGS) -c $(P2_TARGET).cpp

$(P3_TARGET): $(P3_TARGET).o $(TARGET_LIB)
	$(CC) $(P3_TARGET).o -L. -lsparrow -o $(P3_TARGET)

$(P3_TARGET).o: $(P3_TARGET).cpp sparrow.h
	$(CC) $(CFLAGS) -c $(P3_TARGET).cpp

$(P4_TARGET): $(P4_TARGET).o $(TARGET_LIB)
	$(CC) $(P4_TARGET).o -L. -lsparrow -o $(P4_TARGET)

$(P4_TARGET).o: $(P4_TARGET).cpp sparrow.h
	$(CC) $(CFLAGS) -c $(P4_TARGET).cpp

$(TARGET_LIB): sparrow.o
	$(CC) sparrow.o $(LDFLAGS) -o $(TARGET_LIB)

sparrow.o: sparrow.cpp sparrow.h
	$(CC) $(CFLAGS) -c sparrow.cpp

clean:
	$(RM) *.o *.so $(P1_TARGET) $(P1_TEST) $(P2_TARGET) $(P2_TEST) $(P3_TARGET) $(P3_TEST) $(P4_TARGET) $(P4_TEST) $(P5_TEST) $(P6_TEST)