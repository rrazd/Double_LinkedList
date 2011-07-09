project.exe: Double_list_int_driver.o
	g++ Double_list_int_driver.o -o project.exe

Double_list_int_driver.o: ece250.h Exception.h Double_list_int_driver.cpp Double_list_tester.h Double_list.h Double_node_tester.h Double_node.h Tester.h
	g++ -c Double_list_int_driver.cpp

clean:
	rm -f project.exe *.o *~ *#

run:
	./project.exe<int.in


