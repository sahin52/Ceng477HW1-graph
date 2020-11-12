all:
	g++ *.cpp -o raytracer -std=c++11
run:
	g++ *.cpp -o raytracer -std=c++11 && ./raytracer simple.xml
testfile:
	cd Tests && make && ./test && cd ..
kizinki:
	cd CENG477 && cd Homework1 && cd hw1_support_files && make all && ./raytracer simple.xml
sshading:
	g++ *.cpp -o raytracer -std=c++11 && ./raytracer "Sample Scenes/Input Files/simple_shading.xml"