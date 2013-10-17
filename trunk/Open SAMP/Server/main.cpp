
#ifdef WIN32
void StartServer();
#else
extern void StartServer();
#endif

int main()
{
	StartServer();
	return 1;
}
