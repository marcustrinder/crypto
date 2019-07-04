#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include "Project.h"

using namespace std;




int main(){

	// test with p=3 and q=7, message = 12
	RSA test(12, 3, 7);
	
	
	// encrypt message
	test.genPubKey();
	unsigned long long int encrypted = test.encrypt();
	cout <<"Message: " << test.get_data() << endl << "Encrypted message: " << encrypted << endl;


	//decrypt message
	test.set_e_data(encrypted);
	test.genPrivKey();
	unsigned long long int decrypted = test.decrypt();

	cout <<  "Decrypted message:  " << decrypted << endl;

	if (test.get_data() == decrypted)
	{
		cout << "Default constrctor test successful. " << endl;
	}

	

		
		

		// test with randomly generated primes, message = 12
		RSA test2(12);

		
		// encrypt message
		test2.genPubKey();
		unsigned long long int encrypted2 = test2.encrypt();
		cout << "Message: " << test2.get_data() << endl << "Encrypted message: " << encrypted2 << endl;


		//decrypt message
		test2.set_e_data(encrypted2);
		test2.genPrivKey();
		unsigned long long int decrypted2 = test2.decrypt();

		cout << "Decrypted message:  " << decrypted2 << endl;

		if (test2.get_data() == decrypted2)
		{
			cout << "Parametrised constructor test successful. " << endl;
		}
		cout << endl;


		//main program
		cout << "**WELCOME TO THE CRYPTOSYSTEM**" << endl;
		cout << "For RSA algorithm type 'y'." << endl;
		char which;
		cin >> which;
		if (which == 'y')
		{
		menu:

			cout << "RSA Opyions:" << endl;
			cout << "1. Encrypt integer messages." << endl;
			cout << "2. Encrypt plaintext messages." << endl;
			cout << "3. Encrypt a plaintext file." << endl;
			cout << "4. Decrypt an encrypted plaintext file." << endl;
			cout << "Please enter '1', '2', '3' or '4'." << endl;
			char option;
			cin >> option;
			if (option == '1')
			{

				//array of messages
				int *a = NULL;
				cout << "Number of messages? " << endl;
				int N;
				cin >> N;
				a = new int[N];

				// enter N integer messages into array a
				for (int i = 0; i < N; i++)
				{
					int mess;
					cout << "Enter message: " << endl;
					cin >> mess;
					a[i] = mess;
				}

				for (int i = 0; i < N; i++)
				{
					cout << "Message " << i << ": "  << a[i] << endl;
				}

				//input integer messages into RSA constructor
				algo *messages[20];
				for (int i = 0; i < N; i++)
				{
					messages[i] = new RSA(a[i]);
				}
				//generate RSA keys for each message and encrypt
				for (int i = 0; i < N; i++)
				{
					cout << "Message " << i << endl;
					messages[i]->genPubKey();
					messages[i]->genPrivKey();
					unsigned long long int e_mess = messages[i]->encrypt();
					cout << "Encrypted message: " << e_mess << endl;			//print encrypted message
					messages[i]->set_e_data(e_mess);
					cout << "Dercypted message: " << messages[i]->decrypt() << endl;		// print decrypted message
				}
			}

			//plaintext option
			
			else if (option == '2')
			{

				cin.ignore();
				cout << "Insert plaintext message to be encrypted: " << endl;		//enter a plaintext line
				char text[100];
				cin.getline(text, 100);
				int text_int[100];													//converting char array to integer array
				for (unsigned int i = 0; i < strlen(text); i++)
				{
					text_int[i] = text[i];
				}

				//construct RSA object with int messages
				algo *text_messages[100];
				for (unsigned int i = 0; i < strlen(text); i++)
				{
					text_messages[i] = new RSA(text_int[i]);
				}

				cout << "Encrypted message: ";

				for (unsigned int i = 0; i < strlen(text); i++)
				{

					text_messages[i]->genPubKey();
					text_messages[i]->genPrivKey();
					unsigned long long int e_mess = text_messages[i]->encrypt();
					cout << e_mess << endl;
					//cout << text_messages[i]->get_n();
					text_messages[i]->set_e_data(e_mess);

				}
				cout << endl;

				cout << "Decrypted message: ";									//prints both messages


				 int int_text[100];
				char decrypt_text[100];
				for (unsigned int i = 0; i < strlen(text); i++)
				{
					int_text[i] = text_messages[i]->decrypt();
					decrypt_text[i] = int_text[i];
				}

				for (unsigned int i = 0; i < strlen(text); i++)
				{
					cout << decrypt_text[i];
				}
				cout << endl;
			}


			//option to encrypt a plaintext file
			
			else if(option == '3')
			{

				cout << "Please enter file name." << endl;
				string mess_filename;
				cin >> mess_filename;
				string line;
				string lines[100];
				ifstream myfile(mess_filename);				//open text file
				if (myfile.is_open())
				{

					int i = 0;
					while (getline(myfile, line))
					{


						lines[i] = line;					//creates an array of lines

						i++;


					}

					myfile.close();
				}
				else
				{
					cout << "cannot open file." << endl;
				}

				ofstream myfile2;
				myfile2.open("cipher.txt");				//file to be created / written to
				ofstream myfile2_key;
				myfile2_key.open("public_key.txt");

				for (int i = 0; i < 100; i++)
				{
					char text[100];
					strcpy_s(text, lines[i].c_str());			//converts string to char array
					int text_int[100];

					for (unsigned int i = 0; i < strlen(text); i++)
					{
						text_int[i] = text[i];					//then char to int
					}

					algo *text_messages[100];					//constructs RSA object

					for (unsigned int i = 0; i < strlen(text); i++)
					{
						text_messages[i] = new RSA(text_int[i]);
					}

					for (unsigned int i = 0; i < strlen(text); i++)
					{

						text_messages[i]->genPubKey();

						unsigned long long int e_mess = text_messages[i]->encrypt();
						myfile2 <<" " << e_mess ;							//writes encrypted messages to new file "cipher.txt"


						//accesses tuple elements
						myfile2_key <<" " << get<0>(text_messages[i]->sharePubKey()) << "," << get<1>(text_messages[i]->sharePubKey()) << "/" << text_messages[i]->get_n() ;	//shares the public key (e and phi)
						
					}
					myfile2 << endl;
					myfile2_key << endl;
					
				}

				

				myfile2.close();
				myfile2_key.close();


				cout << "Encrypted file 'cipher.txt' and public key 'public_key.txt' created." << endl;
				

			}

			
			else if (option == '4')
			{

						vector<vector<int>> INTS;			//vector of vectors to store encrypted messages (each line) and public key data
						vector<vector<int>> PHI;
						vector<vector<int>> E;
						vector<vector<int>> N;

				string line, key;
				string lines[100], keys[100];
				cout << "Decrypting 'cipher.txt'..." << endl;
				ifstream myfile("cipher.txt");				//opens preselected cipher text file
				ifstream mypubkey("public_key.txt");		//and file containing public data
				if (mypubkey.is_open())
				{ 
					if (myfile.is_open())
					{

						int i = 0;
						while (getline(myfile, line))
						{


							lines[i] = line;
							
							i++;

						}

						
						i = 0;
						while (getline(mypubkey, key))				//reading in file lines and stores into arrays 'lines' and 'keys'
						{
							keys[i] = key;
							i++;
						}





						for (int j = 0; j < 20; j++)
						{
							istringstream ss(lines[j]);
							string token;
							vector<int> ints;
							while (getline(ss, token, ' '))				//here we divide lines into tokens, message data is seperated by spaces
							{											// public key data e, phi and n are seperated by ' ', ',' and '/' respectively

								istringstream iss(token);
								int isss;
								iss >> isss;
								ints.push_back(isss);

							}
							INTS.push_back(ints);

							istringstream keyline(keys[j]);
							string key_token;
							vector<int> keyPhi;
							while (getline(keyline, key_token, ','))
							{
								istringstream ikeyline(key_token);
								int iKey;
								ikeyline >> iKey;
								keyPhi.push_back(iKey);
							}
							PHI.push_back(keyPhi);
							
							
							istringstream e_keyline(keys[j]);
							string key_e;
							vector<int> keyE;
							while (getline(e_keyline, key_e, ' '))
							{
								istringstream e_ikeyline(key_e);
								int ie;
								e_ikeyline >> ie;
								keyE.push_back(ie);
							}
							E.push_back(keyE);

							

							istringstream N_keyline(keys[j]);
							string key_N;
							vector<int> keyN;
							while (getline(N_keyline, key_N, '/'))
							{
								istringstream N_ikeyline(key_N);
								int iN;
								N_ikeyline >> iN;
								keyN.push_back(iN);
							}
							N.push_back(keyN);

							

							cout << endl;


						}


							myfile.close();

					}
				}
				else
				{
					cout << "cannot open file." << endl;
				}

				cout << "Decrypted file: " << endl;

				for (unsigned int p = 0; p < INTS.size(); p++)
				{
					int text_int[100];
					char text[100];
					algo *decryptF[100];
					for (unsigned int i = 1; i < INTS[p].size(); i++)
					{
						decryptF[i] = new RSA();
						decryptF[i]->set_e_data(INTS[p][i]);
						decryptF[i]->genPrivKey(E[p][i], PHI[p][i]);
						text_int[i] = decryptF[i]->decrypt(N[p][i]) ;					//initialsises object RSA with public data and e_data and prints decrypted data
						text[i] = text_int[i];
						cout << text[i] ;
					}
					cout << endl;
				}
						
						mypubkey.close();
			}
			
			else
			{
				cout << "Please enter a valid option." << endl;
			}

			cout << "Return to RSA menu? 'y' / 'n'" << endl;
			char ret;
			cin >> ret;
			if (ret == 'y')
			{
				goto menu;
			}
		}

		else
		{
		cout << "Sorry, no other algorithms loaded yet." << endl;
		}

		
		cout << "Goodbye!" << endl;
	return 0;
}

