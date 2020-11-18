all:
	g++ -v -pthread -O3  *.cpp -o raytracer -std=c++11 
run:
	make all  && ./raytracer "Sample Scenes/Input Files/simple.xml"
testfile:
	cd Tests && make && ./test && cd ..
sshading:
	make all && ./raytracer "Sample Scenes/Input Files/simple_shading.xml"
bunny:
	make all && ./raytracer "Sample Scenes/Input Files/bunny.xml"
cornellbox:
	make all && ./raytracer "Sample Scenes/Input Files/cornellbox.xml"
horseandmug:
	make all && ./raytracer "Sample Scenes/Input Files/horse_and_mug.xml"
killeroo:
	make all && ./raytracer "Sample Scenes/Input Files/killeroo.xml"
mirror_spheres:
	make all && ./raytracer "Sample Scenes/Input Files/mirror_spheres.xml"
sreflectance:
	make all && ./raytracer "Sample Scenes/Input Files/simple_reflectance.xml"
onebyone:
	make run && make sshading && make sreflectance && make bunny && make cornellbox && make mirror_spheres  && make killeroo && make horseandmug 