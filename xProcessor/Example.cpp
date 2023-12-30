#include "xProcessor.h"

xProcessor Cmd;

bool OnChat(const char* cmd)
{
	// If it is not a command, continue..
	if (Cmd.Process(cmd) == false)
	{
		return ((bool(*)(const char*))0x0050E350)(cmd); // 0.97d hook
	}

	return false;
}

void Test(char* szCmd)
{
	printf("Hello world\n");
}

void TestInt(char* szCmd)
{
	if (Cmd.HasArguments() == false || Cmd.IsFirstArgumentStr() == true)
	{
		printf("Usage: %s <number>\n", szCmd);
		return;
	}

	int Number = Cmd.GetTokenInt();

	printf("Number is %d\n", Number);
}

void TestString(char* szCmd)
{
	if (Cmd.HasArguments() == false || Cmd.IsFirstArgumentInt() == true)
	{
		printf("Usage: %s <string>\n", szCmd);
		return;
	}

	char* String = Cmd.GetTokenStr();

	printf("String is %s\n", String);
}

void TestSubCommand(char* szCmd)
{
	if (Cmd.HasArguments() == false || Cmd.IsFirstArgumentInt() == true)
	{
		printf("Usage: %s <command1-command2>\n", szCmd);
		return;
	}

	char* cmd = Cmd.GetTokenStr(false);

	printf("cmd: %s\n", cmd);

	if (strcmp(cmd, "command1") == 0)
	{
		if (Cmd.HasArguments() == false || Cmd.IsFirstArgumentStr() == true)
		{
			printf("Usage: %s command1 <number>\n", szCmd);
			return;
		}

		int Number = Cmd.GetTokenInt();

		printf("Number is %d\n", Number);
	}
	else if (strcmp(cmd, "command2") == 0)
	{
		if (Cmd.HasArguments() == false || Cmd.IsFirstArgumentInt() == true)
		{
			printf("Usage: %s command2 <string>\n", szCmd);
			return;
		}

		char* String = Cmd.GetTokenStr();

		printf("String is %s\n", String);
	}
	else
	{
		printf("Usage: %s <command1-command2>\n", szCmd);
	}
}

void Start()
{
	Cmd.Create("/test",    Test);
	Cmd.Create("/testint", TestInt);
	Cmd.Create("/teststr", TestString);
	Cmd.Create("/testsub", TestSubCommand);
}