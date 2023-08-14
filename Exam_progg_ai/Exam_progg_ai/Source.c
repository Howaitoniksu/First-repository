#include "Header.h"

int read_file(Triangle* arr, int max_size) {
	FILE* file = fopen(FILENAME, "r");
	int count = 0;
	char line[1024];
	while (fgets(line, 1024, file)) {
		double x1, y1, x2, y2, x3, y3;
		if (sscanf(line, "%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3) != 6) {
			printf("Error reading line %d: Invalid format.\n", count + 1);
			continue;
		}
		arr[count].A.x = x1;
		arr[count].A.y = y1;
		arr[count].B.x = x2;
		arr[count].B.y = y2;
		arr[count].C.x = x3;
		arr[count].C.y = y3;
		count++;
		if (count >= max_size) break;
	}
	fclose(file);
	return count;
}

double distance(Point A, Point B) {
	return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}

int is_triangle(Triangle T) {
	double AB = distance(T.A, T.B);
	double BC = distance(T.B, T.C);
	double AC = distance(T.A, T.C);
	if (AB + BC <= AC || AB + AC <= BC || BC + AC <= AB) {
		return 0;
	}
	return 1;
}

double perimeter(Triangle T) {
	double AB = distance(T.A, T.B);
	double BC = distance(T.B, T.C);
	double AC = distance(T.A, T.C);
	return AB + BC + AC;
}

double area(Triangle T) {
	double AB = distance(T.A, T.B);
	double BC = distance(T.B, T.C);
	double AC = distance(T.A, T.C);
	double p = (AB + BC + AC) / 2;
	return sqrt(p * (p - AB) * (p - BC) * (p - AC));
}

void print_info(Triangle T, int number, FILE* file) {
	printf("Triangle %d:\n", number + 1);
	fprintf(file, "Triangle %d:\n", number + 1);
	if (!is_triangle(T)) {
		printf(" Status: Not a triangle.\n");
		fprintf(file, " Status: Not a triangle.\n");
		return;
	}
	double AB = distance(T.A, T.B);
	double BC = distance(T.B, T.C);
	double AC = distance(T.A, T.C);
	printf(" Side AB: %lf\n", AB);
	printf(" Side BC: %lf\n", BC);
	printf(" Side AC: %lf\n", AC);
	printf(" Perimeter: %lf\n", perimeter(T));
	printf(" Area: %lf\n", area(T));
	if (AB * AB + BC * BC == AC * AC || AB * AB + AC * AC == BC * BC || BC * BC + AC * AC == AB * AB) {
		printf(" Type: Right triangle.\n");
		fprintf(file, " Type: Right triangle.\n");
	}
	else if (AB * AB + BC * BC < AC * AC || AB * AB + AC * AC < BC * BC || BC * BC + AC * AC < AB * AB) {
		printf(" Type: Obtuse triangle.\n");
		fprintf(file, " Type: Obtuse triangle.\n");
	}
	else {
		printf(" Type: Acute triangle.\n");
		fprintf(file, " Type: Acute triangle.\n");
	}
}

int main() {
	Triangle arr[10];
	int count = read_file(arr, 10);
	FILE* file = fopen("output.txt", "w");
	for (int i = 0; i < count; i++) {
		print_info(arr[i], i, file);
	}
	fclose(file);
	return 0;
}