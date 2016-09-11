#include <iostream>
#include <string>
#include "Node.h"
#include "Parser.h"
#include "Scanner.h"
#include "Calc.h"
#include "Exception.h"

int main(int argc,char** argv)
{
	EToken toke = TOKEN_BEGIN;
	Calc calc;
	STATUS status = STATUS_OK;
	do
	{
		std::cout << ">";
		std::string buf;
		std::getline(std::cin,buf);
		//std::cout << buf << std::endl;
		Scanner scanner(buf);
		
		if(!scanner.IsEmpty()){
			Parser parser(scanner,calc);
			try{
				status = parser.Parse();
				if(status == STATUS_OK)
				{
					std::cout << parser.Calculate() << std::endl;
				}
			}catch(SyntaxError& e){
				std::cout << e.what() << std::endl;
			}
			catch(Exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			catch(std::bad_alloc& e)
			{
				std::cout << e.what() << std::endl;
			}
			catch(...)
			{
				std::cout << "Unknown error" << std::endl;
			}
		}else{
			std::cout << "Expression is empty" << std::endl;
		}
		status = STATUS_QUIT;
	}while(status != STATUS_QUIT);
	return 0;
}
