#include "Project.h"

//default constructors
RSA::RSA(){

}


RSA::RSA(int mess, unsigned long long int p, unsigned long long int q)
{
	prime1 = p;
	prime2 = q;

	data = mess;
}

//priem ready constr
RSA::RSA(int mess)
{

	//finds a random prime number
	unsigned long long int r1 = (rand() % 1000) + 1;		// the '1000' here gives the maximum value of the rand() function, this program allows upto 64-bit integer
															// the bigger the prime number the more secure the encryption is.
	bool primality = 0;
	while (primality != 1)
	{


		//cout << primality << endl;

		primality = isPrime(r1, 10);
		if (primality == 0)
		{

			r1 = (rand() % 1000) + 1;
		}


	}
	prime1 = r1;
	//cout << r1 << endl;
	//finds a random prime number r2
	unsigned long long int r2 = (rand() % 1000) + 1;

	primality = 0;
	while (primality != 1)
	{


		//cout << primality << endl;

		primality = isPrime(r2, 10);
		if (primality == 0)
		{

			r2 = (rand() % 1000) + 1;
		}


	}
	prime2 = r2;
	//cout << r2 << endl;

	data = mess;

}


//member function to return greastest common denom
tuple<unsigned long long int, int, int> RSA::gcd(unsigned long long int a, unsigned long long int b)
{
	if (a == 0)
	{
		return make_tuple(b, 0, 1);
	}

	unsigned long long int g;
	int  x, y;

	// unpack tuple  returned by function into variables
	tie(g, x, y) = gcd(b % a, a);

	return make_tuple(g, int(y - (b / a) * x), x);
}


//generates public key
unsigned long long int RSA::genPubKey()
{
	unsigned long long int n = prime1 * prime2;
	unsigned long long int phi = (prime1 - 1)*(prime2 - 1);
	//cout <<prime1 << endl << prime2 << endl << phi << endl;
	int e = 3;
	while (1){
		tuple <unsigned long long int, int, int> g = gcd(phi, e);
		unsigned long long int temp = get<0>(g);
		if (temp == 1)
		{
				this->pub_key = e;
	            return e;
		}
		else 
		{
			e++;
		}
		
	}
	


	

}

// generates private key
unsigned long long int RSA::genPrivKey()
{
	unsigned long long int e = this->pub_key;
	unsigned long long int phi = this->get_phi();
	tuple <unsigned long long int, int, int> d = gcd(phi, e);
	
	this->priv_key = (phi + get<2>(d));
	//cout << "priv key: " << this->priv_key << endl;
	return (phi + get<2>(d));
}

unsigned long long int RSA::genPrivKey(unsigned long long int e, unsigned long long int phi)
{
	
	tuple <unsigned long long int, int, int> d = gcd(phi, e);

	this->priv_key = (phi + get<2>(d));
	
	//cout << "priv key: " << this->priv_key << endl;
	return (phi + get<2>(d));
}


// checking for FLT condition
unsigned long long int RSA::power(unsigned long long int a, unsigned long long int n, unsigned long long int p)
{

	unsigned long long int res = 1;
	a = a % p;

	while (n > 0)
	{
		// If n is odd, multiply 'a' with result 
		if (n & 1)
			res = (res*a) % p;

		// n must be even now 
		n = n >> 1; // n = n/2 
		a = (a*a) % p;
	}
	return res;
}

bool RSA::isPrime(unsigned long long int n, int k)
{

	// trivial cases 
	if (n <= 1 || n == 4)  return false;
	if (n <= 3) return true;

	// Try k times 
	while (k>0)
	{
		// pick a random number in [2..n-2]         
		// Above trivial cases make sure that n > 4 
		int a = 2 + rand() % (n - 4);

		// Fermat's little theorem 
		if (power(a, n - 1, n) != 1)
			return false;

		k--;
	}

	return true;
}

// returns p*q
unsigned long long int RSA::get_n() const
{
	unsigned long long int n = prime1 * prime2;
	return n;
}

unsigned long long int RSA::get_phi() const
{
	unsigned long long int phi = (prime1 - 1)*(prime2 - 1);
	return phi;
}

int RSA::get_data() 
{
	return data;
}

//sets encrypted data
void RSA::set_e_data(unsigned long long int e_data_in)
{
	e_data = e_data_in;
}

//derived encryption and decrypton functions
unsigned long long int RSA::encrypt() const
{
	//cout << "p = " << prime1 << endl << "q = " << prime2 << endl;
	

	// 64-bit variables
	unsigned long long int temp = data;
	unsigned long long int e = pub_key;
	unsigned long long int N = get_n();

	// exponent modulo algorithm
	temp %= N;
	unsigned long long int result = 1;
	while (e > 0)
	{
		if (e & 1) result = (result * temp) % N;
		temp = (temp * temp) % get_n();
		e >>= 1;
	}
	return result;

	//int temp = fmod(pow(data, pub_key), this->get_n());
	return result;
	
}

unsigned int RSA::decrypt() const 
{

	//cout << "pub key = " << this->pub_key << endl;
	//cout << "priv key = " << this->priv_key << endl;

	// 64-bit variables
	unsigned long long int temp = e_data;
	unsigned long long int d = priv_key;
	unsigned long long int N = get_n();

	// exponent modulo algorithm

	temp %= N;
	unsigned long long int result = 1;
	while (d > 0) 
	{
		if (d & 1) result = (result * temp) % N;
		temp = (temp * temp) % get_n();
		d >>= 1;
	}
	unsigned int thisResult = unsigned int(result);
	return thisResult;

	
	

}


unsigned int RSA::decrypt(unsigned int n) const
{

	//cout << "pub key = " << this->pub_key << endl;
	//cout << "priv key = " << this->priv_key << endl;

	// 64-bit variables
	unsigned long long int temp = this->e_data;
	unsigned long long int d = this->priv_key;
	

	// exponent modulo algorithm

	temp %= n;
	unsigned long long int result = 1;
	while (d > 0)
	{
		if (d & 1) result = (result * temp) % n;
		temp = (temp * temp) % n;
		d >>= 1;
	}
	unsigned int thisResult = unsigned int(result);
	return thisResult;




}

//pub key tuple
tuple<unsigned long long int, unsigned long long int const> RSA::sharePubKey()
{
	return make_tuple(pub_key, get_phi());
}
