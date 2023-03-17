/*PRIMER PARTE DE PROGRAMA MAMALON*/

#include <iostream>
#include <string>
#include <cstring>
#include <conio.h>

/* Una enumeración es básicamente un conjunto de MACROS que representarán una SECUENCIA DE NÚMEROS.
 * Supongamos que tenemos el arreglo
 *
 *		struct Usuario guapo[ 4 ];
 *
 * Pudiéramos referirnos a ellos como 
 *
 * 		guapo[ 2 ];
 *
 * 	... por ejemplo, pero esto resulta visiblemente poco explícito. Algunas veces le vamos a dar un tratamiento
 * 	especial a cada uno y nos gustaría que se viera a simple vista de quién se trata. En lugar de referirnos
 * 	a ellos como 0, 1, 2, 3... creamos una enumeración que va a representrar también un número pero como si fueran
 * 	macros
 *
 * 		enum Nombre{ YURI, SERTCH, TOCAYO, JUANCA };
 *
 * En automático, YURI tendrá el valor de 0, SERTCH de 1 y así sucesivamente. Siempre en orden ascendente. Puedes
 * especificar algún valor en concreto y el siguiente elemento adoptará ese valor + 1. Opcionalmente puedes especificar
 * con
 *
 * 		: <tipo_de_entero>
 *
 * el tipo de entero que quieres que tenga tu enumeración */
enum Opcion : const std::int16_t { INGRESAR = 1, REGISTRAR_USUARIO, SALIR }; // Para las opciones
enum Tecla : char { BACKSPACE = 8, ENTER = 13 }; // Para las teclas (valor ASCII)
enum ResultadoDeBusqueda : const std::int16_t{ USUARIO_NO_ENCONTRADO, PASSWORD_INCORRECTO, PASSWORD_CORRECTO };

struct Usuario {
	std::string nombre;
	std::string password;
};

/* Aquí usamos una "referencia a una constante" (referencia a un valor temporal constante) para optimizar memoria */
const std::int32_t &MAX_STRING{ 20 };
const std::int32_t &LIMITE_USUARIOS{ 50 };

/* El tipo de datos -auto- hace que el compilador "decida" el tipo de dato que tendrá tu variable en relación
 * al valor o tipo de retorno que le estás asignando.
 *
 * En este caso lo usamos para adoptar la nomenclatura de encabezado de función moderna usando el operador flecha.
 *
 * 		std::int32_t funcion();
 *
 * se puede escribir como
 *
 * 		auto funcion() -> std::int32_t;
 *
 * Al decirle el tipo de retorno de esta forma, el tipo -auto- de alguna manera
 * pierde funcionalidad, pero nos permite expresar los encabezados en este formato màs moderno, usado ademàs
 * por servidores de lenguaje y otros lenguajes como ObjectiveC. Ùsalo si te acomoda y te gusta */
auto leer_datos_usuario() -> struct Usuario;
auto buscar_usuario( const struct Usuario &_UsuarioLeido, const struct Usuario *_DataBase,
		const std::int32_t &_Usuarios ) -> enum ResultadoDeBusqueda;
auto registrar_usuario( struct Usuario *_BaseDatos, std::int32_t *_Usuarios ) -> void;

using std::cout;
using std::cin;

auto main() -> std::int32_t/*{{{*/
{
	struct Usuario usuarios_database[ LIMITE_USUARIOS ];
	const struct Usuario &admin { { "SOYADMIN" }, { "CONTRASENIA" } };
	struct Usuario usuario_leido{ { "" }, { "" } };
	std::int32_t n_registrados{ 0 };

	std::int16_t opcion;

	/* Los atributos son algo del C++ moderno, en este caso el atributo -maybe_unused- nos permite especificarle al
	 * compilador que cierta variable "tal vez no la usemos, pero somos conscientes de ello". Recuerda que cuando
	 * activamos los flags estrictos, hasta eso la hace de pedo. Con esto, nos deja de lanzar advertencia */
	[[ maybe_unused ]] enum ResultadoDeBusqueda resultado_de_busqueda;
	char decision_continuar{ '\0' };
	bool continuar{ true };

	do {
		cout	<< "\n\n\t\t\t              |ESTAS SON LAS OPCIONES|"
				<< "\n\n\t\t\t               1.- INGRESAR"
				<< "\n\n\t\t\t               2.- REGISTRARSE"
				<< "\n\n\t\t\t               3.- SALIR"
				<< "\n\n\t\t\t               * DIGITE LA OPCION: ";
		std::cin >> opcion;
		/* Vaciado de buffer moderno */
		std::cin.ignore();

		switch ( opcion ) {

			case Opcion::INGRESAR:
				if ( n_registrados > 0 ) {
					usuario_leido = leer_datos_usuario();
					resultado_de_busqueda = buscar_usuario( usuario_leido, usuarios_database, n_registrados );
					
					switch ( resultado_de_busqueda ) {
						case USUARIO_NO_ENCONTRADO:
							std::cout << "No mames, ni estas registrado perro" << std::endl;
							break;
						case PASSWORD_INCORRECTO:
							std::cout << "No mames, mete tu password bien qlero" << std::endl;
							break;
						case PASSWORD_CORRECTO:
							std::cout << "Buen ingreso perro" << std::endl;
							break;
					}
				}
				else
					cout << "\n\n\t\t\tNO HAY USUARIOS EN LA BASE DE DATOS";


				cout << "\n\n\t\t\tQUIERES VOLVER AL MENU?: [S]= SI [N]=NO: ";
				cin >> decision_continuar;
				cin.ignore();
				break;

			case Opcion::REGISTRAR_USUARIO:
				cout << "\n\n\t\t\tDEBES INICIAR SESION COMO ADMINISTRADOR PARA TENER "
						"ESTE PRIVILEGIO" << std::endl;
				usuario_leido = leer_datos_usuario();
				std::cout << usuario_leido.nombre << " - " << usuario_leido.password << std::endl;

				if (	usuario_leido.nombre == admin.nombre and
						usuario_leido.password == admin.password and
						n_registrados < LIMITE_USUARIOS ) {

					//registrar_usuario( usuarios_database, &n_registrados );
				}
				else
					cout<<"\n\n\t\t\tNO SE PUEDE INGRESAR"; 

				cout<<"\n\n\t\t\t\t\tQUIERES VOLVER AL MENU?: [S]= SI [N]=NO: ";
				cin >> decision_continuar;
				cin.ignore();
				break;

			case 3:
				cout << "\n\n\t\t\t\t\tHASTA LUEGO :)";
				continuar = false;
				break;

			default:
				cout << "\n\n\t\t\t\t\tOPCION NO VALIDA d:";
				cin.ignore();
				break;
		}
	} while( ( decision_continuar == 'S' or decision_continuar == 's')  and  continuar == true ) ;
}/*}}}*/

auto leer_datos_usuario() -> struct Usuario/*{{{*/
{
	struct Usuario usuario { { "" }, { "" } };

	std::cout << "\n\n\t\t\t+-----------------------+----------------------+";
	std::cout << "\n\n\t\t\t               +|INICIO DE SESION|+ ";
	std::cout << "\n\n\t\t\t+-----------------------+----------------------+";

	std::cout << "\n\n\t\t\t*BIENVENIDO POR FAVOR INGRESE SU USUARIO: ";
	std::cin >> usuario.nombre;

	std::cout << "\n\n\t\t\t*POR FAVOR TECLEE SU CONTRA: " << std::flush;
	char caracter_leido;
	[[ maybe_unused ]] bool continuar{ true };

	while ( continuar ) {
		caracter_leido = static_cast<char>( _getch() );
		if ( caracter_leido == Tecla::ENTER ) {
			continuar = false;
		}
		else if ( caracter_leido == Tecla::BACKSPACE && usuario.password != "" ) {
			usuario.password.pop_back();
			std::cout << "\b \b";
		} else if ( usuario.password.length() < MAX_STRING ) {
			std::cout << '*';
			usuario.password += caracter_leido;
		}
	}

	return usuario;
}/*}}}*/

auto buscar_usuario( const struct Usuario &_UsuarioLeido, const struct Usuario *_BaseDatos,
		const std::int32_t &_UsuariosRegistrados ) -> enum ResultadoDeBusqueda
{
	int32_t i{ 0 };

	// Aquí vamos a implementar el algoritmo de búsqueda, no afuera
	while ( _UsuarioLeido.nombre != ( _BaseDatos + i )->nombre and i < _UsuariosRegistrados )
		++i;

	/* Aquí metemos dos return al estilo Sertch. En estos casos es bien visto "según yo"
	 * porque hay cierto paralelismo (hasta estético) entre ambos returns, no se ve "truncado" */
	if ( i < _UsuariosRegistrados ) {
		if ( _UsuarioLeido.password == _BaseDatos->password ) // Salió antes -> SÍ LO ENCONTRÓ
			return PASSWORD_CORRECTO;
		else
			return PASSWORD_INCORRECTO;
	}
	else
		return USUARIO_NO_ENCONTRADO;
}/*}}}*/

auto registrar_usuario( struct Usuario *_BaseDatos, std::int32_t *_Usuarios ) -> void/*{{{*/
{
	cout	<< "\n\n\t\t\tREGISTRANDO AL USUARIO NUMERO: " << *_Usuarios + 1
			<< "\n\n\t\t\tPOR FAVOR INGRESE SU NOMBRE DE USUARIO: ";
	cin >> ( _BaseDatos + *_Usuarios )->nombre;
	cin.ignore();

	cout << "\n\n\t\t\tINGRESE SU CONTRASEÑA: ";
	cin >> ( _BaseDatos + *_Usuarios )->password;
	cin.ignore();
	
	++( *_Usuarios );
}/*}}}*//*}}}*/
