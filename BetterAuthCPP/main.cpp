#include "includes.h"

std::wstring application_name = L"ExampleBetterAuth";
int main() {
	if (!betterauth::init_application(application_name.c_str())) {
		MessageBoxA(0, "Couldn't find application!", "BetterAuth", 0);
		return 0;
	}

	printf("Options: \n");
	printf("1) Login\n");
	printf("2) Register\n");
	printf("3) Activate key\n");
	printf("4) Check subscription\n");
	printf("5) Get file from server\n");
	bool logged_in = false;
	int operation;
	while (true) {
		std::cin >> operation;
		switch (operation)
		{
		case 1: {
			std::wstring username, password;
			printf("Username: ");
			std::wcin >> username;
			printf("Password: ");
			std::wcin >> password;
			if (betterauth::c_login(username.c_str(), password.c_str())) {
				logged_in = true;
			}
			break;
		}

		case 2: {
			std::wstring username, password;
			printf("Username: ");
			std::wcin >> username;
			printf("Password: ");
			std::wcin >> password;
			if (betterauth::c_register(username.c_str(), password.c_str())) {

			}
			break;
		}

		case 3: {
			//For betterauth::c_activatekey user has to be logged in
			if (!logged_in)
				continue;
			std::wstring key;
			printf("Key: ");
			std::wcin >> key;
			if (betterauth::c_activatekey(key.c_str())) {

			}
			break;
		}

		case 4: {
			//For betterauth::has_sub user has to be logged in
			if (!logged_in)
				continue;
			DWORD productid;
			printf("Which sub do you want to query (Insert product id)\n");
			std::cin >> productid;
			bool has_sub;
			const wchar_t* time_left = betterauth::has_sub(productid, &has_sub);
			
			if (has_sub) {
				printf("User has a sub it will run out on: %ws\n", time_left);

			}
			else
			{
				printf("User doesn't have a sub for this product\n");
			}
			break;
		}
		case 5: {
			//For betterauth::c_activatekey user has to be logged in
			if (!logged_in)
				continue;
			DWORD productid;
			printf("Which product do you want to download\n");
			std::cin >> productid;
			bool has_sub;
			const wchar_t* time_left = betterauth::has_sub(productid, &has_sub);
			if (has_sub) {
				uintptr_t data; DWORD size;
				if (betterauth::get_file(productid, &data, &size)) {
					printf("Downloaded file from server!\n");
				}
				else
				{
					printf("No file provided\n");
				}
			}
			else
			{
				printf("User doesn't have a sub for this product so it can't be downloaded\n");
			}
			break;
		}

		}
	}
	system("pause");
	return 0;
}