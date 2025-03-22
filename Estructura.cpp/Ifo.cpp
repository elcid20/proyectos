
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

struct Producto {
    int id;
    string nombre;
    int cantidad;
    double precio_U;
    Producto* nuevo_P; // Puntero al siguiente producto
};

// Definición estrc cola FIFO
struct Inventario {
    Producto* primer_P;
    Producto* producto_F;
};

// Inicializar inventario
void inicializar_Inven(Inventario* inventario) {
    inventario->primer_P = NULL;
    inventario->producto_F = NULL;
}

// Método para registrar un producto en la cola FIFO
void registrarProducto(Inventario* inventario, int id, string nombre, int cantidad, double precio_U) {
    Producto* nuevo = new Producto; // Reservar memoria
    if (!nuevo) {
        cout << "Error: No se pudo asignar memoria\n";
        return;
    }

    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->cantidad = cantidad;
    nuevo->precio_U = precio_U;
    nuevo->nuevo_P = NULL;

    if (inventario->primer_P == NULL) {
        inventario->primer_P = inventario->producto_F = nuevo;
    } else {
        inventario->producto_F->nuevo_P = nuevo;
        inventario->producto_F = nuevo;
    }

    cout << "Producto registrado: " << nombre << endl;
}

// Método para buscar un producto por ID
Producto* buscarProducto(Inventario* inventario, int id) {
    Producto* aux= inventario->primer_P;
    while (aux) {
        if (aux->id == id) {
            return aux;
        }
        axu = aux->nuevo_P;
    }
    return NULL;
}

// Método para eliminar el primer producto registrado (FIFO)
void eliminarProducto(Inventario* inventario) {
    if (!inventario->primer_P) {
        cout << "El inventario está vacío.\n";
        return;
    }
    if (inventario->primer_P->cantidad > 0) {
        cout << "No se puede eliminar el producto porque aún tiene stock.\n";
        return;
    }

    Producto* temp = inventario->primer_P;
    inventario->primer_P = inventario->primer_P->nuevo_P;
    delete temp;

    if (!inventario->primer_P) {
        inventario->producto_F = NULL;
    }
    cout << "Primer producto eliminado del inventario.\n";
}

// Método para registrar una compra (actualizar cantidad y calcular costo)
void comprarProducto(Inventario* inventario, int id, int cantidadComprada) {
    Producto* prod = buscarProducto(inventario, id);
    if (prod) {
        if (prod->cantidad >= cantidadComprada) {
            prod->cantidad -= cantidadComprada;
            double costoTotal = cantidadComprada * prod->precio_U;
            cout << "Compra realizada: " << cantidadComprada << " unidades de " << prod->nombre << endl;
            cout << "Costo total: $" << costoTotal << endl;
        } else {
            cout << "Stock insuficiente.\n";
        }
    } else {
        cout << "Producto no encontrado.\n";
    }
}

// Método para mostrar todos los productos en el inventario
void mostrarInventario(Inventario* inventario) {
    Producto* axu = inventario->primer_P;
    cout << "\nInventario:\n";
    while (actual) {
        cout << "ID: " << aux->id 
             << " | Nombre: " << aux->nombre 
             << " | Cantidad: " << aux->cantidad 
             << " | Precio: $" << aux->precio_U 
             << " | Costo Total: $" << (aux->cantidad * aux->precio_U) 
             << endl;
        actual = aux->nuevo_P;
    }
}

// Método para calcular el costo total del inventario
void calcularCostoTotal(Inventario* inventario) {
    Producto* aux = inventario->primer_P;
    double costoTotal = 0.0;
    while (aux) {
        costoTotal += aux->cantidad * aux->precio_U;
        actual = aux->nuevo_P;
    }
    cout << "Costo total del inventario: $" << costoTotal << endl;
}


int main() {
    Inventario inventario;
    inicializar_Inven(&inventario);

    registrarProducto(&inventario, 1, "Arroz", 50, 2.5);
    registrarProducto(&inventario, 2, "Frijoles", 30, 3.0);
    registrarProducto(&inventario, 3, "Aceite", 20, 5.0);

    mostrarInventario(&inventario);

    // Comprar productos
    comprarProducto(&inventario, 1, 10);
    comprarProducto(&inventario, 3, 5);

    // Mostrar inventario después de la compra
    mostrarInventario(&inventario);

    // Calcular costo total del inventario
    calcularCostoTotal(&inventario);

    // Intentar eliminar un producto con stock
    eliminarProducto(&inventario);

    // Reducir stock del primer producto a cero y eliminarlo
    comprarProducto(&inventario, 1, 40);
    eliminarProducto(&inventario);

    // Mostrar inventario final
    mostrarInventario(&inventario);

    return 0;
}

