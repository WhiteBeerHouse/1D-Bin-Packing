
#LS: LS.o Data_structure.o
	#${CXX} -g $^ -o $@

#SA: SA.o Data_structure.o
	#${CXX} -g $^ -o $@

TS: TS.o Data_structure.o
	${CXX} -g $^ -o $@

%.o: %.cpp
	${CXX} -g -o $@ -c $^

clean :
	rm -f LS SA TS *.o 