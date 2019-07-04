#include <iostream>
#include <string>
#include <math.h>
#include <tuple>

using namespace std;


#ifndef Project_h
#define Project_h

//BASE CLASS
class algo {
public:
	virtual unsigned long long int encrypt() const = 0;
	virtual unsigned int decrypt() const = 0;
	virtual unsigned int decrypt(unsigned int n) const = 0;

	virtual unsigned long long int genPubKey() = 0;
	virtual unsigned long long int genPrivKey() = 0;
	virtual unsigned long long int genPrivKey(unsigned long long int e, unsigned long long int phi) = 0;
	virtual unsigned long long int get_n() const = 0;


	virtual tuple<unsigned long long int, unsigned long long int const> sharePubKey() = 0;

	virtual void set_e_data(unsigned long long int in) = 0;


};

//DERIVED ABSTRACT CLASS FOR ASSYMETRIC ALGORITHMS
class assymAlgo : public algo{
protected:
	unsigned long long int pub_key;
	unsigned long long int priv_key;
	int data;
	unsigned long long int e_data;
public:
	virtual unsigned long long int encrypt() const = 0;
	virtual unsigned int decrypt() const = 0;
	virtual unsigned int decrypt(unsigned int n) const = 0;

	virtual unsigned long long int genPubKey() = 0;
	virtual unsigned long long int genPrivKey() = 0;
	virtual unsigned long long int genPrivKey(unsigned long long int e, unsigned long long int phi) =0;
	virtual unsigned long long int get_n() const = 0;

	virtual tuple<unsigned long long int, unsigned long long int const> sharePubKey() = 0;


	virtual void set_e_data(unsigned long long int in) = 0;



};

//DERIVED CLASS FOR RSA ALG
class RSA : public assymAlgo{
protected:
	unsigned long long int prime1;
	unsigned long long int prime2;
	//int phi;
	

	
	

public:
	//def constr
	RSA();
	//default constructor takes parameters of message (double, p and q values.
	RSA(int mess, unsigned long long int p, unsigned long long int q);
	//constructor using pregenerated random primes
	RSA(int mess);
	//string rsaEncrypt(string mes);

	// member functions
	unsigned long long int genPubKey();
	unsigned long long int genPrivKey();
    unsigned long long int genPrivKey(unsigned long long int e, unsigned long long int phi);

	unsigned long long int power(unsigned long long int a, unsigned long long int n, unsigned long long int p);
	bool isPrime(unsigned long long int n, int k);

	unsigned long long int get_n() const;
	unsigned long long int get_phi() const;
	int get_data();
	tuple<unsigned long long int, int, int> gcd(unsigned long long int a, unsigned long long int b);

	unsigned long long int encrypt() const;
	void set_e_data(unsigned long long int e_data_in);
	unsigned int decrypt() const;
	unsigned int decrypt(unsigned int n) const ;

	

	tuple<unsigned long long int, unsigned long long int const> sharePubKey();


	virtual ~RSA(){}
};

#endif
