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
		fgets(input, sizeof(input), stdin); // ������ �����Ͽ� ���ڿ��� �Է¹ޱ� ���� fgets�Լ� ���(scanf�δ� �ȵ�)
		
		if (strcmp(input, "\n") == 0) // ��� ���� ���� �Է� �� �ƹ� ���۵� �������� �ʰ� �ʱ���� ����
		{
			printf("\n");
			continue;
		}
		
		input[strlen(input) - 1] = NULL; // ���ڿ� �������� ���� �Էµ� ���๮�ڸ� ����� ���� NULL ����
		
		command = strtok(input, " ");

		if (strcmp(command, "set") == 0)
		{
			command_set(ip_address, id, age, alarm); // ���� �Է�
		}
		else if (strcmp(command, "get") == 0)
		{
			command_get(ip_address, id, age, alarm); // ���� ���
		}
		else if (strcmp(command, "help") == 0)
		{
			printf("�����Դϴ�.\n���� �Է� ����� �ñ��ϸ� \"set /?\"�� ���� ��� ����� �ñ��ϸ� \"get /?\"�� �Է��ϼ���.\n\n");
		}
		else if (strcmp(command, "exit") == 0)
		{
			printf("�����մϴ�.\n\n");
			break;
		}
		else
		{
			printf("�߸��� ����Դϴ�.\n\n");
			continue;
		}
	}

	return 0;
}

// �����͸� �Է��ϴ� �Լ�
int command_set(char *ip_address, char *id, char *age, char *alarm)
{
	char *temp[10] = { NULL, } , correct_check_temp[20] = { 0, }, *correct_check, using_check[4] = { 0, };
	int i = 0, j = 0, check_count = 0, positional_number_check = 0;

	do
	{
		temp[i] = strtok(NULL, " "); // �Էµ� �����͵��� ������� ������ �迭�� ����
		i++;
	} while (temp[i - 1] != NULL);

	if (temp[0] == NULL)
	{
		printf("�߸��� �Է��Դϴ�.\n\n");
		return -1;
	}

	for (i = 0; (i < 8) && (temp[i] != NULL); i = i + 2)
	{
		if ((strcmp(temp[i], "/?") != 0) && (temp[i + 1] == NULL))
		{
			printf("�߸��� �Է��Դϴ�.\n\n");
			return -1;
		}

		// ip ���� �Է�
		if (strcmp(temp[i], "ip") == 0)
		{
			strncpy_s(correct_check_temp, 20, temp[i + 1], strlen(temp[i + 1])); // ip�� ���� �̿��� �ٸ� ������ �ԷµǾ����� Ȯ���ϱ� ���� ip�� �Էµ� �����͸� ����
			
			correct_check = strtok(correct_check_temp, ".");

			while (correct_check != NULL)
			{	
				j = 0;
				positional_number_check = 0;

				// ip�� ���� �̿��� �ٸ� ������ �ԷµǾ����� Ȯ��
				while (correct_check[j] != NULL)
				{
					if ((correct_check[j]<'0') || (correct_check[j]>'9'))
					{
						printf("�߸��� �Է��Դϴ�.\n\n");
						return -1;
					}

					positional_number_check++;
					j++;
				}

				//ip �ּ��� �� �ڸ����� 1�� 3 �������� Ȯ��
				if (positional_number_check < 1 || positional_number_check>3)
				{
					printf("�߸��� �Է��Դϴ�.\n\n");
					return -1;
				}

				correct_check = strtok(NULL, ".");

				check_count++;
			}

			if (check_count != 4)
			{
				printf("�߸��� �Է��Դϴ�.\n\n");
				return -1;
			}
			
			strncpy_s(ip_address, 20, temp[i + 1], strlen(temp[i + 1])); // 20 ũ���� ���ۿ� strlen(temp[i + 1]) ���̸�ŭ �����ϰ� ���� �ڵ����� NULL ����
			using_check[0] = 1; // �Է� �Ǿ����� üũ�ϴ� flag
		}
		// id ���� �Է�
		else if (strcmp(temp[i], "id") == 0)
		{
			strncpy_s(id, 20, temp[i + 1], strlen(temp[i + 1]));
			using_check[1] = 1;
		}
		// age ���� �Է�
		else if (strcmp(temp[i], "age") == 0)
		{
			strncpy_s(correct_check_temp, 20, temp[i + 1], strlen(temp[i + 1])); // age�� ���� �̿��� �ٸ� ������ �ԷµǾ����� Ȯ���ϱ� ���� age�� �Էµ� �����͸� ����

			j = 0;

			// age�� ���� �̿��� �ٸ� ������ �ԷµǾ����� Ȯ��
			while (correct_check_temp[j] != NULL)
			{
				if ((correct_check_temp[j]<'0') || (correct_check_temp[j]>'9'))
				{
					printf("�߸��� �Է��Դϴ�.\n\n");
					return -1;
				}

				j++;
			}

			strncpy_s(age, 5, temp[i+ 1], strlen(temp[i + 1]));
			using_check[2] = 1;
		}
		// alarm ���� �Է�
		else if (strcmp(temp[i], "alarm") == 0)
		{
			// alarm�� True / False �� �̿��� �ٸ� ������ �ԷµǾ����� Ȯ��
			if (!((strcmp(temp[i + 1], "True") == 0) || (strcmp(temp[i + 1], "true") == 0) || (strcmp(temp[i + 1], "T") == 0) || (strcmp(temp[i + 1], "t") == 0) || (strcmp(temp[i + 1], "False") == 0) || (strcmp(temp[i + 1], "false") == 0) || (strcmp(temp[i + 1], "F") == 0) || (strcmp(temp[i + 1], "f") == 0)))
			{
				printf("�߸��� �Է��Դϴ�.\n\n");
				return -1;
			}

			strncpy_s(alarm, 7, temp[i + 1], strlen(temp[i + 1]));
			using_check[3] = 1;
		}
		else if (strcmp(temp[i], "/?") == 0)
		{
			printf("set ip ***.***.***.*** id ****** age ** alarm (True/False) �� ���·� �Է��ϼ���\n\n");
			return 0;
		}
		else
		{
			printf("�߸��� �Է��Դϴ�.\n\n");
			return -1;
		}
	}

	// � ������ �ԷµǾ����� ���
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

	printf("������ �ԷµǾ����ϴ�.\n\n");

	return 0;
}

// �����͸� ����ϴ� �Լ�
int command_get(char *ip_address, char *id, char *age, char *alarm)
{
	char *temp;
	
	temp = strtok(NULL, " ");

	if (temp == NULL)
	{
		printf("�߸��� �Է��Դϴ�.\n\n");
		return -1;
	}

	if ((strcmp(temp, "ip") == 0) && (ip_address[0] != 0)) // ���ϴ� �����Ͱ� ip�̰� ip �����Ͱ� �ԷµǾ����� ��쿡�� ���
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
		printf("%s ������ ���� �Էµ��� �ʾҽ��ϴ�.\n\n", temp);
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

			printf("������ ���� �Էµ��� �ʾҽ��ϴ�.\n");
		}

		printf("\n");
	}
	else if (strcmp(temp, "/?") == 0)
	{
		printf("get (ip/id/age/alarm) �� ���·� �Է��ϼ���.\n\n");
	}
	else
	{
		printf("�߸��� �Է��Դϴ�.\n\n");
		return -1;
	}
}