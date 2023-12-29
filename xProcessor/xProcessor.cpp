#include "Init.h"

xProcessor::xProcessor()
{
	Index = 0;
	szCmd = NULL;

	for (int i = 0; i < MAX_CMDS; i++)
	{
		Commands[i].Init();
	}
}

xProcessor::~xProcessor()
{
}

xCCMD* xProcessor::Create(const char* Id, void func(char* szCmd))
{
	if (Index > MAX_CMDS)
	{
		printf("[xProcessor::Create] Commands limit reached, consider incrementing MAX_CMDS\n");
		return NULL;
	}

	xCCMD* c = &Commands[Index];

	memcpy(c->sId, Id, MAX_CMD_LENGTH);
	c->sId[MAX_CMD_LENGTH - 1] = NULL;
	c->func = func;
	memset(c->TokenString, NULL, sizeof(c->TokenString));

	printf(COLOR_WHITE, "[xProcessor::Create] %s Index: %d\n", Id, Index);

	Index++;

	return c;
}

bool xProcessor::Process(const char* Input)
{
	char szCmd[MAX_CMD_LENGTH] = { NULL };

	ParseCommand(Input, szCmd);

	xCCMD* cmd = GetCommand(szCmd);

	if (cmd == NULL)
	{
		return false;
	}

	if (cmd->func == NULL)
	{
		printf("[xProcessor::Process] Command (%s) does not have a default function.\n", szCmd);
		return false;
	}

	SetActiveCommand(cmd);

	memset(cmd->TokenString, NULL, sizeof(cmd->TokenString));
	memcpy(cmd->TokenString, Input, strlen(Input));

	cmd->TokenIndex = strlen(szCmd) + 1;
	cmd->func(szCmd);

	SetActiveCommand(NULL);
	return true;
}

xCCMD* xProcessor::GetCommand(const char* Id)
{
	for (int i = 0; i < MAX_CMDS; i++)
	{
		xCCMD* cmd = &Commands[i];

		if (strcmp(cmd->sId, Id) == 0)
		{
			return cmd;
		}
	}

	return NULL;
}

bool xProcessor::IsCommand(const char* Id)
{
	if (Id[0] == '/' || Id[0] == '\'')
	{
		return true;
	}

	return false;
}

void xProcessor::Execute(const char* szCmd)
{
	Process(szCmd);
}

bool isNumber(char* num)
{
	if (atoi(num) != 0)
	{
		return true;
	}

	if (atoi(num) == 0 && num[0] == '0')
	{
		return true;
	}

	return false;
}

char* xProcessor::GetTokenStr(bool RestoreIndex, bool IncludeSpaces)
{
	xCCMD* cmd = GetActiveCommand();

	if (cmd)
	{
		int StartToken = cmd->TokenIndex;
		int i = 0;
		bool Success = false;

		while (true)
		{
			if (cmd->TokenString[cmd->TokenIndex] == NULL || i > (MAX_ARGUMENT_LENGTH - 1))
			{
				if ((cmd->TokenIndex + 1) < MAX_ARGUMENT_LENGTH)
				{
					cmd->TokenIndex++;
				}
				break;
			}

			if (cmd->TokenString[cmd->TokenIndex] == CHAR_SPACE)
			{
				if (isNumber(&cmd->TokenString[cmd->TokenIndex + 1]) == true)
				{
					if (!RestoreIndex)
					{
						cmd->TokenString[cmd->TokenIndex] = NULL;
					}

					cmd->TokenIndex++;
					break;
				}
			}

			if (IncludeSpaces == false)
			{
				if (cmd->TokenString[cmd->TokenIndex] == CHAR_SPACE)
				{
					if (!RestoreIndex)
					{
						cmd->TokenString[cmd->TokenIndex] = NULL;
					}

					cmd->TokenIndex++;
					break;
				}
			}

			Success = true;
			cmd->TokenIndex++;
			i++;
		}

		if (Success && isNumber(&cmd->TokenString[StartToken]) == false)
		{
			if (RestoreIndex)
			{
				cmd->TokenIndex = StartToken;
			}

			return &cmd->TokenString[StartToken];
		}
		else
		{
			cmd->TokenIndex = StartToken;
			return INVALID_STR;
		}
	}

	return INVALID_STR;
}

int xProcessor::GetTokenInt(bool RestoreIndex)
{
	xCCMD* cmd = GetActiveCommand();

	if (cmd == NULL)
	{
		return INVALID_INT;
	}

	int StartToken = cmd->TokenIndex;
	int count = 0;

	while (true)
	{
		if (cmd->TokenString[cmd->TokenIndex] == NULL || count > (MAX_ARGUMENT_LENGTH - 1))
		{
			if ((cmd->TokenIndex + 1) < MAX_ARGUMENT_LENGTH)
			{
				cmd->TokenIndex++;
			}
			break;
		}

		if (cmd->TokenString[cmd->TokenIndex] == CHAR_SPACE)
		{
			if (!RestoreIndex)
			{
				cmd->TokenString[cmd->TokenIndex] = NULL;
			}

			cmd->TokenIndex++;
			break;
		}

		cmd->TokenIndex++;
		count++;
	}

	if (isNumber(&cmd->TokenString[StartToken]) == true)
	{
		if (RestoreIndex)
		{
			cmd->TokenIndex = StartToken;
		}

		return atoi(&cmd->TokenString[StartToken]);
	}
	else
	{
		cmd->TokenIndex = StartToken;
		return INVALID_INT;
	}
}

void xProcessor::ParseCommand(const char* Input, char* szCmd)
{
	int i = 0;

	for (i = 0; i < MAX_CMD_LENGTH; i++)
	{
		if (Input[i] == ' ' || Input[i] == NULL)
		{
			break;
		}

		szCmd[i] = Input[i];
	}

	szCmd[i] = NULL;
}

void xProcessor::SetActiveCommand(xCCMD* cmd)
{
	szCmd = cmd;
}

bool xProcessor::HasArguments()
{
	if (Cmd.GetTokenInt(true) == INVALID_INT && Cmd.GetTokenStr(true) == INVALID_STR)
	{
		return false;
	}

	return true;
}

bool xProcessor::IsFirstArgumentInt()
{
	if (Cmd.GetTokenInt(true) != INVALID_INT)
	{
		return true;
	}

	return false;
}

bool xProcessor::IsFirstArgumentStr()
{
	if (Cmd.GetTokenStr(true) != INVALID_STR)
	{
		return true;
	}

	return false;
}

xCCMD* xProcessor::GetActiveCommand()
{
	return szCmd;
}