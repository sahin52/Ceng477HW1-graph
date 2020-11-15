all:
	g++ *.cpp -o raytracer -std=c++11
run:
	g++ *.cpp -o raytracer -std=c++11 && ./raytracer simple.xml
testfile:
	cd Tests && make && ./test && cd ..
kizinki:
	cd CENG477 && cd Homework1 && cd hw1_support_files && make all && time ./raytracer simple.xml
sshading:
	g++ *.cpp -o raytracer -std=c++11 && ./raytracer "Sample Scenes/Input Files/simple_shading.xml"
bunny:
	g++ *.cpp -o raytracer -std=c++11 -O3 && ./raytracer "Sample Scenes/Input Files/bunny.xml"
cornelbox:
	g++ *.cpp -o raytracer -std=c++11 && ./raytracer "Sample Scenes/Input Files/cornellbox.xml"
horseandmug:
	g++ *.cpp -o raytracer -std=c++11 && ./raytracer "Sample Scenes/Input Files/horse_and_mug.xml"
killeroo:
	g++ *.cpp -o raytracer -std=c++11 && ./raytracer "Sample Scenes/Input Files/killeroo.xml"
mirror_spheres:
	g++ *.cpp -o raytracer -std=c++11 && ./raytracer "Sample Scenes/Input Files/mirror_spheres.xml"
sreflectance:
	g++ *.cpp -o raytracer -std=c++11 && ./raytracer "Sample Scenes/Input Files/simple_reflectance.xml"
kizinkisshading:
	cd CENG477 && cd Homework1 && cd hw1_support_files && make all && ./raytracer "hw1_sample_scenes/simple_shading.xml"
kizinkihorseandmug:
	cd CENG477 && cd Homework1 && cd hw1_support_files && make all && ./raytracer "hw1_sample_scenes/horse_and_mug.xml"