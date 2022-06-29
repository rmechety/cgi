#include <cstdlib>
#include <cstdio>

int main(int argc, char const *argv[])
{
	const char *env_p = getenv("HOME");
    if (env_p)
        printf("%s = %s\n", "HOME", env_p);
	return 0;
}
