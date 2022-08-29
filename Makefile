CXXFLAGS = --std=c++17 
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

all: manga

debug: CXXFLAGS += -g
debug: manga

manga: src/main.o src/mainwin.o src/entrydialog.o src/store.o src/order.o src/customer.o src/item.o src/product.o src/plant.o src/tool.o src/mulch.o src/*.h
	$(CXX) $(CXXFLAGS) src/main.o src/mainwin.o src/entrydialog.o src/store.o src/order.o src/customer.o src/item.o src/product.o src/plant.o src/tool.o src/mulch.o $(GTKFLAGS) -o manga
src/main.o: src/main.cpp src/*.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp $(GTKFLAGS) -o src/main.o
src/mainwin.o: src/mainwin.cpp src/*.h
	$(CXX) $(CXXFLAGS) -c src/mainwin.cpp $(GTKFLAGS) -o src/mainwin.o
src/entrydialog.o: src/entrydialog.cpp src/*.h
	$(CXX) $(CXXFLAGS) -c src/entrydialog.cpp $(GTKFLAGS) -o src/entrydialog.o
src/store.o: src/store.cpp src/*.h
	$(CXX) $(CXXFLAGS) -c src/store.cpp -o src/store.o
src/order.o: src/order.cpp src/*.h
	$(CXX) $(CXXFLAGS) -c src/order.cpp -o src/order.o
src/customer.o: src/customer.cpp src/*h
	$(CXX) $(CXXFLAGS) -c src/customer.cpp -o src/customer.o
src/item.o: src/item.cpp src/*.h
	$(CXX) $(CXXFLAGS) -c src/item.cpp -o src/item.o
product.o: src/product.cpp src/*.h
	$(CXX) $(CXXFLAGS) -c src/product.cpp -o src/product.o
src/plant.o: src/plant.cpp src/*.h
	$(CXX) $(CXXFLAGS) -c src/plant.cpp -o src/plant.o
src/tool.o: src/tool.cpp src/*.h
	$(CXX) $(CXXFLAGS) -c src/tool.cpp -o src/tool.o
src/mulch.o: src/mulch.cpp src/*.h
	$(CXX) $(CXXFLAGS) -c src/mulch.cpp -o src/mulch.o


clean:
	rm -f src/*.o src/*.gch ~* a.out manga

