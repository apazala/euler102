#include <stdio.h>
#include <inttypes.h>

int64_t area2(int x0, int y0, int x1, int y1, int x2, int y2)
{
	int64_t ux = x1 - x0;
	int64_t uy = y1 - y0;
	int64_t vx = x2 - x0;
	int64_t vy = y2 - y0;
	int64_t a1 = ux*vy;
	int64_t a2 = uy*vx;

    //abs(det(u | v)) -> area of the parallelogram: twice the area of the triangle
	return (a1>a2 ? a1 - a2 : a2 - a1);
}


int main()
{
	FILE *fp = fopen("p102_triangles.txt", "r");
	if(!fp)
	{
		fprintf(stderr, "Cant de more\n");
		return 1;
	}

	int x0, y0, x1, y1, x2, y2;

	int ans = 0;
	while (fscanf(fp, "%d,%d,%d,%d,%d,%d", &x0, &y0, &x1, &y1, &x2, &y2) == 6)
	{
		int64_t a = area2(x0, y0, x1, y1, x2, y2);
		if (!a) continue;

        //compute areas susbtituting one the vertex by (0, 0). sum of all 3 == 'a' -> contains (0,0)
		int64_t lastarea = area2(0, 0, x1, y1, x2, y2);
		if (!lastarea || lastarea >= a)continue;
		a -= lastarea;

		lastarea = area2(x0, y0, 0, 0, x2, y2);
		if (!lastarea || lastarea >= a)continue;
		a -= lastarea;

		lastarea = area2(x0, y0, x1, y1, 0, 0);
		if (!lastarea)continue;

		if (a == lastarea) 
			ans++;
	}

	printf("%d\n", ans);

	return 0;
}
