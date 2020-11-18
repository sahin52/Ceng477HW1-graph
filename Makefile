all:
	g++ *.cpp -o raytracer -std=c++11
run:
	g++ *.cpp -o raytracer -std=c++11 && ./raytracer "Sample Scenes/Input Files/simple.xml"
testfile:
	cd Tests && make && ./test && cd ..
sshading:
	g++ *.cpp -o raytracer -std=c++11 && ./raytracer "Sample Scenes/Input Files/simple_shading.xml"
bunny:
	g++ *.cpp -o raytracer -std=c++11 -O3 && ./raytracer "Sample Scenes/Input Files/bunny.xml"
cornellbox:
	g++ *.cpp -o raytracer -std=c++11 && ./raytracer "Sample Scenes/Input Files/cornellbox.xml"
horseandmug:
	g++ *.cpp -o raytracer -std=c++11 && ./raytracer "Sample Scenes/Input Files/horse_and_mug.xml"
killeroo:
	g++ *.cpp -o raytracer -std=c++11 && ./raytracer "Sample Scenes/Input Files/killeroo.xml"
mirror_spheres:
	g++ *.cpp -o raytracer -std=c++11 && ./raytracer "Sample Scenes/Input Files/mirror_spheres.xml"
sreflectance:
	g++ *.cpp -o raytracer -std=c++11 && ./raytracer "Sample Scenes/Input Files/simple_reflectance.xml"
onebyone:
	make run && make sshading && make sreflectance && make bunny && make cornellbox && make mirror_spheres  && make killeroo && make horseandmug 