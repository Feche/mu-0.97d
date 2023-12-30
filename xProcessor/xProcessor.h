#pragma once

#define MAX_CMD_LENGTH			20
#define MAX_ARGUMENT_LENGTH		100
#define MAX_CMDS				100

#define CHAR_SPACE				0x20

#define INVALID_STR				NULL
#define INVALID_INT				(0x7FFFFFFF)

#define IsInt(n)				((n == INVALID_INT) ? false : true)
#define DefaultInt(p, d)		(p = (IsInt(p)) ? p : d)

struct xCCMD
{
	void Init()
	{
		func = NULL;
		TokenIndex = 0;
		memset(sId, NULL, MAX_CMD_LENGTH);
		memset(TokenString, NULL, (MAX_ARGUMENT_LENGTH + MAX_CMD_LENGTH));
	}

	char	sId[MAX_CMD_LENGTH];
	char	TokenString[(MAX_ARGUMENT_LENGTH + MAX_CMD_LENGTH)];
	int		TokenIndex;
	void	(*func)(char* szCmd);
};

class xProcessor
{
public:
	xProcessor();
	~xProcessor();

private:
	xCCMD	Commands[MAX_CMDS];
	xCCMD*	szCmd;
	int		Index;

public:
	xCCMD*	Create(const char* Id, void func(char* szCmd));
	xCCMD*	GetCommand(const char* Id);
	xCCMD*	GetActiveCommand();
	void	SetActiveCommand(xCCMD* cmd);
	bool	Process(const char* Input);
	bool	IsCommand(const char* Id);
	void	Execute(const char* szCmd);
	char*	GetTokenStr(bool IncludeSpaces = true, bool RestoreIndex = false);
	int		GetTokenInt(bool RestoreIndex = false);
	void	ParseCommand(const char* Input, char* szCmd);
	bool	HasArguments();
	bool	IsFirstArgumentInt();
	bool	IsFirstArgumentStr();
};