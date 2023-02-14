#include <iostream>
#include "error.h"
#include "personne.h"

/**
 * struct test - Struct of an option 
 * @test: the test
 * @func: the function associated to this option
 */
typedef struct test {
    std::string test;
    void (*func)();
} test_t;


void test1()
{
    std::cout << "Everything is okay";
    exit (OK);
}

/**
 * @brief test_creation_modification - Création et modification d'une personne
 */
void test_creation_modification()
{
    personne p{"PRICE", "Josh", "0606", "test@gmail.com"};

    std::cout << p.nomComplet() << std::endl;
    p.setNom("DOH");
    p.setPrenom("John");
    std::cout << p.nomComplet() << std::endl;
    exit(OK);
}

/**
 * @brief test_update_mail - Test mise à jour email
 */
void test_update_mail()
{
    personne p{"DOH", "John", "0606", "test@gmail.com"};

    std::cout << p.email() << std::endl;
    p.setEmail("john.doe@gmail.com");
    std::cout << p.email() << std::endl;
    exit(OK);
}

/**
 * @brief test_update_numero - Test mise à jour numero
 */
void test_update_numero()
{
    personne p{"DOH", "John", "0606060606", "test@gmail.com"};

    std::cout << p.numero() << std::endl;
    p.setNumero("0707070707");
    std::cout << p.numero() << std::endl;
    exit(OK);
}

/**
 * @brief test_affiche_personne - Test affiche personne
 */
void test_affiche_personne()
{
    personne p{"DOH", "John", "0606060606", "john.doe@gmail.com"};

    p.affiche();
    exit(OK);
}

/**
 * @brief test_lire_personne - Test lire personne
 */
void test_lire_personne()
{
    personne p{};

    p.lire();
    p.affiche();
    exit(OK);
}

/**
 * @brief test_mauvais_numero - Création d'une personne avec mauvais numero
 */
void test_mauvais_numero()
{
    personne p{"DOH", "John", "060606", "john.doe@gmail.com"};

    exit(p.status());
}

/**
 * @brief test_mauvais_email - Création d'une personne avec mauvais email
 */
void test_mauvais_email()
{
    personne p{"DOH", "John", "0606060606", "johngmail.com"};

    exit(p.status());
}

/**
 * @brief test_update_avec_mauvais_email - Modification du mail avec un mauvais
 */
void test_update_avec_mauvais_email()
{
    personne p{};

    p.setEmail("johngmail.com");
    exit(p.status());
}

/**
 * @brief test_update_avec_mauvais_numero - Modification du numero avec un mauvais
 */
void test_update_avec_mauvais_numero()
{
    personne p{};

    p.setNumero("06060");
    exit(p.status());
}

int main(int argc, char **argv)
{
    unsigned int i = 0;
	test_t tests[] = {
		{"test1", test1},
		{"test_creation_modification", test_creation_modification},
		{"test_update_mail", test_update_mail},
		{"test_update_numero", test_update_numero},
		{"test_affiche_personne", test_affiche_personne},
		{"test_lire_personne", test_lire_personne},
		{"test_mauvais_numero", test_mauvais_numero},
		{"test_mauvais_email", test_mauvais_email},
		{"test_update_avec_mauvais_email", test_update_avec_mauvais_email},
		{"test_update_avec_mauvais_numero", test_update_avec_mauvais_numero},
		{"", NULL}
	};

    if (argc > 1)
    {
        while (tests[i].func != NULL && tests[i].test.compare(argv[1]))
            i++;

        if (tests[i].test != "")
            tests[i].func();
    }

    exit(0);
}