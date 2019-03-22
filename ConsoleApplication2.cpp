


// ConsoleApplication2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "Vec3.h"
#include "ppm.h"
#include "Ray.h"
#include "spherer.h"
#include "HitableList.h"
#include "float.h"
#include "camera.h"
#include "Material.h"
#include "randGenerator.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;



//float hit_sphere(const vec3& center, float radius, const ray& r) {
//	vec3 oc = r.origin() - center;
//	float a = dot(r.direction(), r.direction());
//	float b = 2.0 * dot(oc, r.direction());
//	float c = dot(oc, oc) - radius * radius;
//	float descriminant = b * b - 4 * a*c;
//	if (descriminant < 0) {
//		return -1.0;
//	}
//	else {
//		return (-b -sqrt(descriminant))/(2.0*a);
//	}
//}

//float randNumber() {
//	float resultat = float((rand() / float(RAND_MAX)));
//	if (resultat < 1) {
//		return resultat;
//	}
//	else {
//		return randNumber();
//	}
//}

vec3 color(const ray& r, hitable *world, int depth) {
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec)) {
		ray scattered;
		vec3 attenuation;
		if ((depth < 50) && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}
		else {
			return vec3(0,0,0);
		}
	}
	else {
		vec3 unitDirection = unit_vector(r.direction());
		float t = 0.5*(unitDirection.y() + 1.0);
		vec3 color = (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
		return(color);
	}
}



//vec3 color(const ray& r, hitable *world, int depth) {
//	hit_record rec;
//	if (world->hit(r, 0.001, MAXFLOAT, rec)) {
//		ray scattered;
//		vec3 attenuation;
//		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
//			return attenuation * color(scattered, world, depth + 1);
//		}
//		else {
//			return vec3(0, 0, 0);
//		}
//	}
//	else {
//		vec3 unit_direction = unit_vector(r.direction());
//		float t = 0.5*(unit_direction.y() + 1.0);
//		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
//	}
//}



hitable *random_scene() {
	int n = 500;
	hitable **list = new hitable*[n + 1];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = randGenerator::Generate();
			vec3 center(a + 0.9* randGenerator::Generate(), 0.2, b + 0.9* randGenerator::Generate());
			if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
				if (choose_mat < 0.8) {  // diffuse
					list[i++] = new sphere(center, 0.2, new lambertian(vec3(randGenerator::Generate()* randGenerator::Generate(),  randGenerator::Generate()* randGenerator::Generate(),  randGenerator::Generate()* randGenerator::Generate())));
				}
				else if (choose_mat < 0.95) { // metal
					list[i++] = new sphere(center, 0.2,
						new metal(vec3(0.5*(1 +  randGenerator::Generate()), 0.5*(1 +  randGenerator::Generate()), 0.5*(1 +  randGenerator::Generate())), 0.5* randGenerator::Generate()));
				}
				else {  // glass
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
	list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

	return new hitable_list(list, i);
}


int main()
{
	int nx = 200;
	int ny = 100;
	int ns = 100;


	PPM ppm;
	ppm.setHeight(nx);
	ppm.setWidth(ny);

	//vec3 lower_left_corner(-2.0, -1.0, -1.0);
	//vec3 horizontal(4.0, 0.0, 0.0);
	//vec3 vertical(0.0, 2.0, 0.0);
	//vec3 origin(0.0, 0.0, 0.0);


	//hitable *liste[5];
	


	
	//float R = cos(M_PI/4);
	//liste[0] = new sphere(vec3(-R, 0, -1), R, new lambertian(vec3(0,0,1)));
	//liste[1] = new sphere(vec3(R, 0, -1), R, new lambertian(vec3(1,0,0)));

	//liste[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
	//liste[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	//liste[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8,0.6,0.2), 0.0));
	//liste[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
	//liste[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));
	
	//hitable *world = new hitable_list(liste, 5);
	hitable *world = random_scene();

	vec3 lookfrom(13, 2, 3);
	vec3 lookat(0,0,0);
	float dist_to_focus = 10.0;
	float aperture = 0.1;
	camera cam(lookfrom, lookat, vec3(0,1,0), 20, float(nx)/float(ny), aperture, dist_to_focus);
	
	
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0,0,0);
			for (int s = 0; s < ns; s++)
			{
				//float test1 = float((rand() / float(RAND_MAX)));
				//float test2 = float((rand() / float(RAND_MAX)));
				float test1 = randGenerator::Generate();
				float test2 = randGenerator::Generate();
				float u = float(i + test1) / float(nx);
				float v = float(j + test2) / float(ny);

				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col+= color(r, world, 0);

			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			vec3 data(ir, ig, ib);
			ppm.addData(data);
			//cout << ir << " " << ig << " " << ib << "\n";
			
		}
	}

	ppm.save("C:/Users/eleve/Desktop/uuuuuf/testPPM.ppm");
	
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
