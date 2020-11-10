all:
	g++ *.cpp -o raytracer -std=c++11
run:
	g++ *.cpp -o raytracer -std=c++11 ; ./raytracer simple.xml
testfile:
	cd Tests && make && ./test && cd ..
