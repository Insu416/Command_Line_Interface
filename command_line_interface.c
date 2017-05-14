#include <stdio.h>
#include <string.h>

int command_set(char *ip_address, char *id, char *age, char *alarm);
int command_get(char *ip_address, char *id, char *age, char *alarm);

int main()
{
	char input[70] = { 0, };
	char *command = NULL;
	char ip_address[20] = {0, }, id[20] = {0, }, age[5] = {0, }, alarm[7] = {0, };

	while(1)
	{
		printf(">> ");
		fgets(input, sizeof(input), stdin); // 공백을 포함하여 문자열을 입력받기 위해 fgets함수 사용(scanf로는 안됨)
		
		if (strcmp(input, "\n") == 0) // 명령 없이 엔터 입력 시 아무 동작도 실행하지 않고 초기상태 유지
		{
			printf("\n");
			continue;
		}
		
		input[strlen(input) - 1] = NULL; // 문자열 마지막에 같이 입력된 개행문자를 지우기 위해 NULL 삽입
		
		command = strtok(input, " ");

		if (strcmp(command, "set") == 0)
		{
			command_set(ip_address, id, age, alarm); // 정보 입력
		}
		else if (strcmp(command, "get") == 0)
		{
			command_get(ip_address, id, age, alarm); // 정보 출력
		}
		else if (strcmp(command, "help") == 0)
		{
			printf("도움말입니다.\n정보 입력 방법이 궁금하면 \"set /?\"을 정보 출력 방법이 궁금하면 \"get /?\"을 입력하세요.\n\n");
		}
		else if (strcmp(command, "exit") == 0)
		{
			printf("종료합니다.\n\n");
			break;
		}
		else
		{
			printf("잘못된 명령입니다.\n\n");
			continue;
		}
	}

	return 0;
}

// 데이터를 입력하는 함수
int command_set(char *ip_address, char *id, char *age, char *alarm)
{
	char *temp[10] = { NULL, } , correct_check_temp[20] = { 0, }, *correct_check, using_check[4] = { 0, };
	int i = 0, j = 0, check_count = 0, positional_number_check = 0;

	do
	{
		temp[i] = strtok(NULL, " "); // 입력된 데이터들을 순서대로 포인터 배열에 저장
		i++;
	} while (temp[i - 1] != NULL);

	if (temp[0] == NULL)
	{
		printf("잘못된 입력입니다.\n\n");
		return -1;
	}

	for (i = 0; (i < 8) && (temp[i] != NULL); i = i + 2)
	{
		if ((strcmp(temp[i], "/?") != 0) && (temp[i + 1] == NULL))
		{
			printf("잘못된 입력입니다.\n\n");
			return -1;
		}

		// ip 정보 입력
		if (strcmp(temp[i], "ip") == 0)
		{
			strncpy_s(correct_check_temp, 20, temp[i + 1], strlen(temp[i + 1])); // ip에 숫자 이외의 다른 정보가 입력되었는지 확인하기 위해 ip로 입력된 데이터를 복사
			
			correct_check = strtok(correct_check_temp, ".");

			while (correct_check != NULL)
			{	
				j = 0;
				positional_number_check = 0;

				// ip에 숫자 이외의 다른 정보가 입력되었는지 확인
				while (correct_check[j] != NULL)
				{
					if ((correct_check[j]<'0') || (correct_check[j]>'9'))
					{
						printf("잘못된 입력입니다.\n\n");
						return -1;
					}

					positional_number_check++;
					j++;
				}

				//ip 주소의 각 자릿수가 1과 3 사이인지 확인
				if (positional_number_check < 1 || positional_number_check>3)
				{
					printf("잘못된 입력입니다.\n\n");
					return -1;
				}

				correct_check = strtok(NULL, ".");

				check_count++;
			}

			if (check_count != 4)
			{
				printf("잘못된 입력입니다.\n\n");
				return -1;
			}
			
			strncpy_s(ip_address, 20, temp[i + 1], strlen(temp[i + 1])); // 20 크기의 버퍼에 strlen(temp[i + 1]) 길이만큼 복사하고 끝에 자동으로 NULL 삽입
			using_check[0] = 1; // 입력 되었는지 체크하는 flag
		}
		// id 정보 입력
		else if (strcmp(temp[i], "id") == 0)
		{
			strncpy_s(id, 20, temp[i + 1], strlen(temp[i + 1]));
			using_check[1] = 1;
		}
		// age 정보 입력
		else if (strcmp(temp[i], "age") == 0)
		{
			strncpy_s(correct_check_temp, 20, temp[i + 1], strlen(temp[i + 1])); // age에 숫자 이외의 다른 정보가 입력되었는지 확인하기 위해 age로 입력된 데이터를 복사

			j = 0;

			// age에 숫자 이외의 다른 정보가 입력되었는지 확인
			while (correct_check_temp[j] != NULL)
			{
				if ((correct_check_temp[j]<'0') || (correct_check_temp[j]>'9'))
				{
					printf("잘못된 입력입니다.\n\n");
					return -1;
				}

				j++;
			}

			strncpy_s(age, 5, temp[i+ 1], strlen(temp[i + 1]));
			using_check[2] = 1;
		}
		// alarm 정보 입력
		else if (strcmp(temp[i], "alarm") == 0)
		{
			// alarm에 True / False 값 이외의 다른 정보가 입력되었는지 확인
			if (!((strcmp(temp[i + 1], "True") == 0) || (strcmp(temp[i + 1], "true") == 0) || (strcmp(temp[i + 1], "T") == 0) || (strcmp(temp[i + 1], "t") == 0) || (strcmp(temp[i + 1], "False") == 0) || (strcmp(temp[i + 1], "false") == 0) || (strcmp(temp[i + 1], "F") == 0) || (strcmp(temp[i + 1], "f") == 0)))
			{
				printf("잘못된 입력입니다.\n\n");
				return -1;
			}

			strncpy_s(alarm, 7, temp[i + 1], strlen(temp[i + 1]));
			using_check[3] = 1;
		}
		else if (strcmp(temp[i], "/?") == 0)
		{
			printf("set ip ***.***.***.*** id ****** age ** alarm (True/False) 의 형태로 입력하세요\n\n");
			return 0;
		}
		else
		{
			printf("잘못된 입력입니다.\n\n");
			return -1;
		}
	}

	// 어떤 정보가 입력되었는지 출력
	for (i = 0; i < 4; i++)
	{
		if (using_check[i] == 1)
			if (i == 0)
				printf("ip ");
			else if (i == 1)
				printf("id ");
			else if (i == 2)
				printf("age ");
			else if (i == 3)
				printf("alarm ");
	}

	printf("정보가 입력되었습니다.\n\n");

	return 0;
}

// 데이터를 출력하는 함수
int command_get(char *ip_address, char *id, char *age, char *alarm)
{
	char *temp;
	
	temp = strtok(NULL, " ");

	if (temp == NULL)
	{
		printf("잘못된 입력입니다.\n\n");
		return -1;
	}

	if ((strcmp(temp, "ip") == 0) && (ip_address[0] != 0)) // 원하는 데이터가 ip이고 ip 데이터가 입력되어있을 경우에만 출력
		printf("%s\n\n", ip_address);
	else if ((strcmp(temp, "id") == 0) && (id[0] != 0))
		printf("%s\n\n", id);
	else if ((strcmp(temp, "age") == 0) && (age[0] != 0))
		printf("%s\n\n", age);
	else if ((strcmp(temp, "alarm") == 0) && (alarm[0] != 0))
	{
		if ((strcmp(alarm, "True") == 0) || (strcmp(alarm, "true") == 0) || (strcmp(alarm, "T") == 0) || (strcmp(alarm, "t") == 0))
			printf("True\n\n");
		else if ((strcmp(alarm, "False") == 0) || (strcmp(alarm, "false") == 0) || (strcmp(alarm, "F") == 0) || (strcmp(alarm, "f") == 0))
			printf("False\n\n");
	}
	else if (((strcmp(temp, "ip") == 0) && (ip_address[0] == 0)) || ((strcmp(temp, "id") == 0) && (id[0] == 0)) || ((strcmp(temp, "age") == 0) && (age[0] == 0)) || ((strcmp(temp, "alarm") == 0) && (alarm[0] == 0)))
		printf("%s 정보가 아직 입력되지 않았습니다.\n\n", temp);
	else if (strcmp(temp, "all") == 0)
	{
		printf("%s %s %s %s\n", ip_address, id, age, alarm);

		if ((ip_address[0] == 0) || (id[0] == 0) || (age[0] == 0) || (alarm[0] == 0))
		{
			if (ip_address[0] == 0)
				printf("ip ");
			
			if (id[0] == 0)
				printf("id ");

			if (age[0] == 0)
				printf("age ");

			if (alarm[0] == 0)
				printf("alarm ");

			printf("정보가 아직 입력되지 않았습니다.\n");
		}

		printf("\n");
	}
	else if (strcmp(temp, "/?") == 0)
	{
		printf("get (ip/id/age/alarm) 의 형태로 입력하세요.\n\n");
	}
	else
	{
		printf("잘못된 입력입니다.\n\n");
		return -1;
	}
}