#include <stdio.h>

template<typename Type1, typename Type2>

class Template {

public:
	Type1 a;
	Type2 b;

	Template(Type1 a, Type2 b) : a(a), b(b) {}

	Template Min(Type1 a, Type2 b) {

		if (a < b)
		{
			return static_cast<Type1>(a);
		}
		else
		{
			return static_cast<Type2>(b);
		}
	}
};

int main()
{
	Template<int, int> a(10, 20);
	Template<int, float> b(10, 20);
	Template<int, double> c(10, 20);
	Template<float, double> d(10, 20);
	Template<float, float> e(10, 20);
	Template<double, double> f(10, 20);


	printf("int int %d\n", a.Min(1, 2));
	printf("int float %d\n", b.Min(1, 2.0));
	printf("int double %lf\n", c.Min(1, 2.0));
	printf("double float %lf\n", d.Min(1, 2.0));
	printf("float float %f\n", e.Min(1.0, 2.0));
	printf("double double %lf\n", f.Min(1.0, 2.0));

	return 0;
}