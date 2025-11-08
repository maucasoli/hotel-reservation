#include <iostream>
#include <string>
#include <msclr/marshal_cppstd.h>
#include <chrono>
#include <thread>

#include <sqlite3.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

void startDatabase() {
	sqlite3* db;
	char* errorMessage = nullptr;

	// open or create DB
	int rc = sqlite3_open("database_hotel.db", &db);
	if (rc) {
		MessageBox::Show("Error opening database: " + gcnew String(sqlite3_errmsg(db)), "SQLite Error");
		return;
	}

	// create table query
	const char* createTableQuery = "CREATE TABLE IF NOT EXISTS chambres ("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"chambre TEXT NOT NULL, "
		"nom TEXT NOT NULL, "
		"prenom TEXT NOT NULL, "
		"reserve TEXT NOT NULL);";

	// execute table creation query
	rc = sqlite3_exec(db, createTableQuery, nullptr, nullptr, &errorMessage);
	if (rc != SQLITE_OK) {
		MessageBox::Show("Error creating table: " + gcnew String(errorMessage), "SQLite Error");
		sqlite3_free(errorMessage);
		sqlite3_close(db);
		return;
	}

	// check if table is empty
	const char* countQuery = "SELECT COUNT(*) FROM chambres;";
	sqlite3_stmt* stmt;
	int rowCount = 0;


	rc = sqlite3_prepare_v2(db, countQuery, -1, &stmt, nullptr);
	if (rc == SQLITE_OK) {
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			rowCount = sqlite3_column_int(stmt, 0);
		}
		sqlite3_finalize(stmt);
	}
	else {
		MessageBox::Show("Error checking table count: " + gcnew String(sqlite3_errmsg(db)), "SQLite Error");
		sqlite3_close(db);
		return;
	}



	if (rowCount == 0) {
		for (int i = 1; i <= 9; i++) {
			std::string chambre = std::to_string(100 + i);

			// spaces to use searchReservation()
			std::string nom = " ";
			std::string prenom = " ";
			std::string reserve = "non";

			std::string insertQuery = "INSERT INTO chambres (chambre, nom, prenom, reserve) VALUES ('"
				+ chambre + "', '"
				+ nom + "', '"
				+ prenom + "', '"
				+ reserve + "');";

			// c_str(): ponteiro para a var
			rc = sqlite3_exec(db, insertQuery.c_str(), nullptr, nullptr, &errorMessage);
			if (rc != SQLITE_OK) {
				MessageBox::Show("Error inserting data: " + gcnew String(errorMessage), "SQLite Error");
				sqlite3_free(errorMessage);
			}
		}
	}
}
void createReservation(System::Windows::Forms::ComboBox^ comboBox, System::Windows::Forms::TextBox^ txtNom, System::Windows::Forms::TextBox^ txtPrenom) {
	if (comboBox->SelectedIndex == -1) {
		MessageBox::Show("Remplir chambre");
		return;
	}
	else if (String::IsNullOrEmpty(txtNom->Text)) {
		MessageBox::Show("Nom ne peut pas etre vide");
		return;
	}
	else if (String::IsNullOrEmpty(txtPrenom->Text)) {
		MessageBox::Show("Prenom ne peut pas etre vide");
		return;
	}

	String^ ansChambre = comboBox->SelectedItem->ToString();
	String^ ansNom = txtNom->Text;
	String^ ansPrenom = txtPrenom->Text;

	// convert managed string to unmanaged
	msclr::interop::marshal_context context;
	std::string chambre = context.marshal_as<std::string>(ansChambre);
	std::string nom = context.marshal_as<std::string>(ansNom);
	std::string prenom = context.marshal_as<std::string>(ansPrenom);


	sqlite3* db;
	char* errorMessage = nullptr;

	int rc = sqlite3_open("database_hotel.db", &db);
	if (rc) {
		MessageBox::Show("Error opening database: " + gcnew String(sqlite3_errmsg(db)), "SQLite Error");
		return;
	}

	sqlite3_stmt* stmt;
	std::string check_room = "SELECT reserve FROM chambres WHERE chambre = '" + chambre + "'";
	const char* res;

	rc = sqlite3_prepare_v2(db, check_room.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		// converte o retorno de sqlite3_column_text para um ponteiro const char*
		res = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
	}
	else if (rc == SQLITE_DONE) {
		std::cerr << "Consulta não retornou resultados." << std::endl;
	}
	else {
		std::cerr << "Erro ao executar consulta: " << sqlite3_errmsg(db) << std::endl;
	}


	// check if already reserved
	if (std::string(res) == "oui") {
		MessageBox::Show("Chambre déjà reservée");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return;
	}


	std::string updateQuery = "UPDATE chambres SET "
		"nom = '" + nom + "', "
		"prenom = '" + prenom + "', "
		"reserve = 'oui' "
		"WHERE chambre = '" + chambre + "';";

	rc = sqlite3_exec(db, updateQuery.c_str(), nullptr, nullptr, &errorMessage);
	if (rc != SQLITE_OK) {
		MessageBox::Show("Error inserting data: " + gcnew String(errorMessage), "SQLite Error");
		sqlite3_free(errorMessage);
	}
	else {
		MessageBox::Show("La réservation a été réalisée!", "Succès");
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	comboBox->SelectedIndex = -1;
	txtNom->Text = "";
	txtPrenom->Text = "";
}
void deleteReservation(System::Windows::Forms::ComboBox^ comboBox, System::Windows::Forms::TextBox^ txtNom, System::Windows::Forms::TextBox^ txtPrenom) {
	if (comboBox->SelectedIndex == -1) {
		MessageBox::Show("Remplir chambres");
		return;
	}
	else if (String::IsNullOrEmpty(txtNom->Text)) {
		MessageBox::Show("Nom ne peut pas etre vide");
		return;
	}
	else if (String::IsNullOrEmpty(txtPrenom->Text)) {
		MessageBox::Show("Prenom ne peut pas etre vide");
		return;
	}

	String^ ansChambre = comboBox->SelectedItem->ToString();
	String^ ansNom = txtNom->Text;
	String^ ansPrenom = txtPrenom->Text;

	msclr::interop::marshal_context context;
	std::string chambre = context.marshal_as<std::string>(ansChambre);
	std::string nom = context.marshal_as<std::string>(ansNom);
	std::string prenom = context.marshal_as<std::string>(ansPrenom);


	sqlite3* db;
	char* errorMessage = nullptr;

	int rc = sqlite3_open("database_hotel.db", &db);
	if (rc) {
		MessageBox::Show("Error opening database: " + gcnew String(sqlite3_errmsg(db)), "SQLite Error");
		return;
	}


	sqlite3_stmt* stmt;
	std::string check_room =
		"SELECT nom, prenom, reserve "
		"FROM chambres "
		"WHERE chambre = '" + chambre + "'";

	const char* check_nom;
	const char* check_prenom;
	const char* check_reserve;

	rc = sqlite3_prepare_v2(db, check_room.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		check_nom = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		check_prenom = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		check_reserve = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

	}
	else if (rc == SQLITE_DONE) {
		std::cerr << "Consulta não retornou resultados." << std::endl;
	}
	else {
		std::cerr << "Erro ao executar consulta: " << sqlite3_errmsg(db) << std::endl;
	}

	// check if already reserved
	if (std::string(check_reserve) == "non") {
		MessageBox::Show("Chambre est libre");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return;
	}
	else if (std::string(check_nom) != nom) {
		MessageBox::Show("Nom incorrect");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return;
	}
	else if (std::string(check_prenom) != prenom) {
		MessageBox::Show("Prenom incorrect");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return;
	}


	std::string insertQuery = "UPDATE chambres SET nom = ' ', prenom = ' ', reserve = 'non' WHERE chambre = '" + chambre + "';";

	rc = sqlite3_exec(db, insertQuery.c_str(), nullptr, nullptr, &errorMessage);
	if (rc != SQLITE_OK) {
		MessageBox::Show("Error inserting data: " + gcnew String(errorMessage), "SQLite Error");
		sqlite3_free(errorMessage);
	}
	else {
		MessageBox::Show("La réservation a été annulée!", "Succès");
	}

	sqlite3_close(db);

	comboBox->SelectedIndex = -1;
	txtNom->Text = "";
	txtPrenom->Text = "";
}
void modifyNom(System::Windows::Forms::ComboBox^ comboBox, System::Windows::Forms::TextBox^ txtNom, System::Windows::Forms::TextBox^ txtPrenom) {
	if (comboBox->SelectedIndex == -1) {
		MessageBox::Show("Remplir chambre");
		return;
	}
	else if (String::IsNullOrEmpty(txtNom->Text)) {
		MessageBox::Show("Nom ne peut pas etre vide");
		return;
	}
	else if (String::IsNullOrEmpty(txtPrenom->Text)) {
		MessageBox::Show("Prenom ne peut pas etre vide");
		return;
	}

	String^ ansChambre = comboBox->SelectedItem->ToString();
	String^ ansNom = txtNom->Text;
	String^ ansPrenom = txtPrenom->Text;

	// convert managed string to unmanaged (std::string)
	msclr::interop::marshal_context context;
	std::string chambre = context.marshal_as<std::string>(ansChambre);
	std::string nom = context.marshal_as<std::string>(ansNom);
	std::string prenom = context.marshal_as<std::string>(ansPrenom);


	sqlite3* db;
	char* errorMessage = nullptr;

	int rc = sqlite3_open("database_hotel.db", &db);
	if (rc) {
		MessageBox::Show("Error opening database: " + gcnew String(sqlite3_errmsg(db)), "SQLite Error");
		return;
	}


	sqlite3_stmt* stmt;
	std::string check_room =
		"SELECT reserve "
		"FROM chambres "
		"WHERE chambre = '" + chambre + "'";


	const char* check_reserve;

	rc = sqlite3_prepare_v2(db, check_room.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		check_reserve = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

	}
	else if (rc == SQLITE_DONE) {
		std::cerr << "Consulta não retornou resultados." << std::endl;
	}
	else {
		std::cerr << "Erro ao executar consulta: " << sqlite3_errmsg(db) << std::endl;
	}

	// check if already reserved
	if (std::string(check_reserve) == "non") {
		MessageBox::Show("Chambre est libre");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return;
	}


	std::string insertQuery = "UPDATE chambres SET nom = '" + nom + "', prenom = '" + prenom + "' WHERE chambre = '" + chambre + "';";

	rc = sqlite3_exec(db, insertQuery.c_str(), nullptr, nullptr, &errorMessage);
	if (rc != SQLITE_OK) {
		MessageBox::Show("Error inserting data: " + gcnew String(errorMessage), "SQLite Error");
		sqlite3_free(errorMessage);
	}
	else {
		MessageBox::Show("La réservation a été modifiée!", "Succès");
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	comboBox->SelectedIndex = -1;
	txtNom->Text = "";
	txtPrenom->Text = "";
}
void modifyChambre(System::Windows::Forms::ComboBox^ comboBox, System::Windows::Forms::ComboBox^ comboBoxNew, System::Windows::Forms::TextBox^ txtNom, System::Windows::Forms::TextBox^ txtPrenom) {
	if (comboBox->SelectedIndex == -1 || comboBoxNew->SelectedIndex == -1) {
		MessageBox::Show("Remplir chambres");
		return;
	}
	else if (String::IsNullOrEmpty(txtNom->Text)) {
		MessageBox::Show("Nom ne peut pas etre vide");
		return;
	}
	else if (String::IsNullOrEmpty(txtPrenom->Text)) {
		MessageBox::Show("Prenom ne peut pas etre vide");
		return;
	}

	String^ ansChambre = comboBox->SelectedItem->ToString();
	String^ ansChambreNew = comboBoxNew->SelectedItem->ToString();
	String^ ansNom = txtNom->Text;
	String^ ansPrenom = txtPrenom->Text;

	// convert managed string to unmanaged (std::string)
	msclr::interop::marshal_context context;
	std::string chambre = context.marshal_as<std::string>(ansChambre);
	std::string chambreNew = context.marshal_as<std::string>(ansChambreNew);
	std::string nom = context.marshal_as<std::string>(ansNom);
	std::string prenom = context.marshal_as<std::string>(ansPrenom);


	sqlite3* db;
	char* errorMessage = nullptr;

	int rc = sqlite3_open("database_hotel.db", &db);
	if (rc) {
		MessageBox::Show("Error opening database: " + gcnew String(sqlite3_errmsg(db)), "SQLite Error");
		return;
	}


	sqlite3_stmt* stmt;
	std::string check_room_old = "SELECT nom, prenom, reserve "
		"FROM chambres "
		"WHERE chambre = '" + chambre + "'";
	std::string check_room_new = "SELECT reserve "
		"FROM chambres "
		"WHERE chambre = '" + chambreNew + "'";
	const char* check_nom;
	const char* check_prenom;
	const char* check_reserve;
	const char* check_reserve_new;

	rc = sqlite3_prepare_v2(db, check_room_old.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		check_nom = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		check_prenom = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		check_reserve = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
	}
	else if (rc == SQLITE_DONE) {
		std::cerr << "Consulta não retornou resultados." << std::endl;
	}
	else {
		std::cerr << "Erro ao executar consulta: " << sqlite3_errmsg(db) << std::endl;
	}


	std::string check_nom_str = check_nom ? std::string(check_nom) : "";
	std::string check_prenom_str = check_prenom ? std::string(check_prenom) : "";
	std::string check_reserve_str = check_reserve ? std::string(check_reserve) : "";


	if (std::string(check_reserve_str) == "non") {
		MessageBox::Show("Current chambre est libre");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return;
	}
	else if (std::string(check_nom_str) != nom || std::string(check_prenom_str) != prenom) {
		MessageBox::Show("Nom ou prenom incorrect");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return;
	}
	else sqlite3_finalize(stmt);


	rc = sqlite3_prepare_v2(db, check_room_new.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		check_reserve_new = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

	}
	else if (rc == SQLITE_DONE) {
		std::cerr << "Consulta não retornou resultados." << std::endl;
	}
	else {
		std::cerr << "Erro ao executar consulta: " << sqlite3_errmsg(db) << std::endl;
	}
	std::string check_reserve_new_str = check_reserve_new ? std::string(check_reserve_new) : "";


	if (std::string(check_reserve_new_str) == "oui") {
		MessageBox::Show("New chambre est déjà reservée");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return;
	}
	else sqlite3_finalize(stmt);

	std::string copyQuery = "UPDATE chambres SET "
		"nom = (SELECT nom FROM chambres WHERE chambre = '" + chambre + "'), "
		"prenom = (SELECT prenom FROM chambres WHERE chambre = '" + chambre + "'), "
		"reserve = (SELECT reserve FROM chambres WHERE chambre = '" + chambre + "') "
		"WHERE chambre = '" + chambreNew + "';";

	// execute insertion query
	rc = sqlite3_exec(db, copyQuery.c_str(), nullptr, nullptr, &errorMessage);
	if (rc != SQLITE_OK) {
		MessageBox::Show("Error inserting data: " + gcnew String(errorMessage), "SQLite Error");
		sqlite3_free(errorMessage);
	}



	// erase older reservation
	std::string deleteQuery = "UPDATE chambres SET nom = ' ', prenom = ' ', reserve = 'non' WHERE chambre = '" + chambre + "';";

	rc = sqlite3_exec(db, deleteQuery.c_str(), nullptr, nullptr, &errorMessage);
	if (rc != SQLITE_OK) {
		MessageBox::Show("Error inserting data: " + gcnew String(errorMessage), "SQLite Error");
		sqlite3_free(errorMessage);
	}
	else {
		MessageBox::Show("La chambre a été modifiée!", "Succès");
	}

	sqlite3_close(db);

	comboBox->SelectedIndex = -1;
	comboBoxNew->SelectedIndex = -1;
	txtNom->Text = "";
	txtPrenom->Text = "";
}
void displayReservations(System::Windows::Forms::RichTextBox^ richTextBox1) {
	richTextBox1->Text = "";

	const char* dbPath = "database_hotel.db";
	sqlite3* db;
	sqlite3_stmt* stmt;


	int rc = sqlite3_open(dbPath, &db);
	if (rc) {
		MessageBox::Show("Não foi possível abrir o banco de dados", "Erro", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	const char* sqlQuery = "SELECT * FROM chambres ORDER BY chambre;";

	rc = sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		MessageBox::Show("Erro ao preparar a consulta", "Erro", MessageBoxButtons::OK, MessageBoxIcon::Error);
		sqlite3_close(db);
		return;
	}

	// vars for receiving results
	const char* col1;
	const char* col2;
	const char* col3;
	const char* col4;

	// put results in the richtextbox
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		col1 = (const char*)sqlite3_column_text(stmt, 1); // chambre
		col2 = (const char*)sqlite3_column_text(stmt, 2); // nom
		col3 = (const char*)sqlite3_column_text(stmt, 3); // prenom
		col4 = (const char*)sqlite3_column_text(stmt, 4); // réservation

		// convert to managed to put in the richtextbox
		richTextBox1->AppendText("---------------\n");
		String^ result = "Chambre " + gcnew String(col1);
		richTextBox1->AppendText(result + "\n");
		richTextBox1->AppendText("---------------\n");
		result = "Nom: " + gcnew String(col2);
		richTextBox1->AppendText(result + "\n");
		result = "Prénom: " + gcnew String(col3);
		richTextBox1->AppendText(result + "\n");
		richTextBox1->AppendText("Réservée: ");
		result = gcnew String(col4);
		if (gcnew String(col4) == "non") {
			richTextBox1->SelectionColor = System::Drawing::Color::Red;
			richTextBox1->AppendText(result + "\n\n");
		}
		else {
			richTextBox1->SelectionColor = System::Drawing::Color::Green;
			result = gcnew String(col4);
			richTextBox1->AppendText(result + "\n\n");
		}

		// default color
		richTextBox1->SelectionColor = System::Drawing::Color::Black;

	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	//displayReservations(richTextBox1);

}
bool confirmation() {
	MessageBoxButtons buttons = MessageBoxButtons::YesNo;
	DialogResult result;

	result = MessageBox::Show("Are you sure?", "Confirmation", buttons);
	if (result == DialogResult::No) {
		return false;
	}

	return true;
}
void eraseTable() {
	sqlite3* db;
	char* errorMessage = nullptr;

	int rc = sqlite3_open("database_hotel.db", &db);
	if (rc) {
		MessageBox::Show("Error opening database: " + gcnew String(sqlite3_errmsg(db)), "SQLite Error");
		return;
	}

	const char* createTableQuery = "CREATE TABLE IF NOT EXISTS chambres ("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"chambre TEXT NOT NULL, "
		"nom TEXT NOT NULL, "
		"prenom TEXT NOT NULL, "
		"reserve TEXT NOT NULL);";


	rc = sqlite3_exec(db, createTableQuery, nullptr, nullptr, &errorMessage);
	if (rc != SQLITE_OK) {
		MessageBox::Show("Error creating table: " + gcnew String(errorMessage), "SQLite Error");
		sqlite3_free(errorMessage);
		sqlite3_close(db);
		return;
	}

	for (int i = 1; i <= 9; i++) {
		std::string chambre = std::to_string(100 + i);
		std::string nom = " ";
		std::string prenom = " ";
		std::string reserve = "non";

		std::string insertQuery =
			"UPDATE chambres "
			"SET nom = '" + nom + "', prenom = '" + prenom + "', reserve = '" + reserve + "' "
			"WHERE chambre = '" + chambre + "';";

		rc = sqlite3_exec(db, insertQuery.c_str(), nullptr, nullptr, &errorMessage);
		if (rc != SQLITE_OK) {
			MessageBox::Show("Error inserting data: " + gcnew String(errorMessage), "SQLite Error");
			sqlite3_free(errorMessage);
		}
	}
}
void searchReservation(System::Windows::Forms::ComboBox^ comboBox, System::Windows::Forms::TextBox^ txtNom, System::Windows::Forms::TextBox^ txtPrenom, System::Windows::Forms::RichTextBox^ richTextBox1) {
	richTextBox1->Text = "";

	String^ ansChambre = "";
	if (comboBox->SelectedIndex != -1) {
		ansChambre = comboBox->SelectedItem->ToString();
	}
	String^ ansNom = txtNom->Text;
	String^ ansPrenom = txtPrenom->Text;

	// convert managed string to unmanaged (std::string)
	msclr::interop::marshal_context context;
	std::string chambre = context.marshal_as<std::string>(ansChambre);
	std::string nom = context.marshal_as<std::string>(ansNom);
	std::string prenom = context.marshal_as<std::string>(ansPrenom);

	const char* dbPath = "database_hotel.db";
	sqlite3* db;
	sqlite3_stmt* stmt;

	int rc = sqlite3_open(dbPath, &db);
	if (rc) {
		MessageBox::Show("Não foi possível abrir o banco de dados", "Erro", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	std::string query = "SELECT * FROM chambres WHERE chambre = '" + chambre + "' OR nom = '" + nom + "' OR prenom = '" + prenom + "';";

	const char* sqlQuery = query.c_str();

	// prepare query
	rc = sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		MessageBox::Show("Erro ao preparar a consulta", "Erro", MessageBoxButtons::OK, MessageBoxIcon::Error);
		sqlite3_close(db);
		return;
	}

	// vars to receive reults
	const char* col1;
	const char* col2;
	const char* col3;
	const char* col4;


	while (sqlite3_step(stmt) == SQLITE_ROW) {
		col1 = (const char*)sqlite3_column_text(stmt, 1); // chambre
		col2 = (const char*)sqlite3_column_text(stmt, 2); // nom
		col3 = (const char*)sqlite3_column_text(stmt, 3); // prenom
		col4 = (const char*)sqlite3_column_text(stmt, 4); // réservation

		richTextBox1->AppendText("----------------\n");
		String^ result = "Chambre " + gcnew String(col1);
		richTextBox1->AppendText(result + "\n");
		richTextBox1->AppendText("----------------\n");
		result = "Nom: " + gcnew String(col2);
		richTextBox1->AppendText(result + "\n");
		result = "Prénom: " + gcnew String(col3);
		richTextBox1->AppendText(result + "\n");
		richTextBox1->AppendText("Réservée: ");
		result = gcnew String(col4);
		if (gcnew String(col4) == "non") {
			richTextBox1->SelectionColor = System::Drawing::Color::Red;
			richTextBox1->AppendText(result + "\n\n");
		}
		else {
			richTextBox1->SelectionColor = System::Drawing::Color::Green;
			result = gcnew String(col4);
			richTextBox1->AppendText(result + "\n\n");
		}

		// default color
		richTextBox1->SelectionColor = System::Drawing::Color::Black;

	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	comboBox->SelectedIndex = -1;
	txtNom->Text = "";
	txtPrenom->Text = "";
}
void echangerReservations() {
	sqlite3* db;
	char* errorMessage = nullptr;

	int rc = sqlite3_open("database_hotel.db", &db);
	if (rc) {
		MessageBox::Show("Error opening database: " + gcnew String(sqlite3_errmsg(db)), "SQLite Error");
		return;
	}

	std::string nom, prenom, reserve;
	std::string backup = "SELECT nom, prenom, reserve FROM chambres WHERE chambre = 109;";
	sqlite3_stmt* stmt;

	rc = sqlite3_prepare_v2(db, backup.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Erro na preparação da consulta SELECT: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return;
	}

	// execute SELECT query and get results
	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		nom = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		prenom = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		reserve = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

		std::cout << "Data received: " << nom << ", " << prenom << ", " << reserve << std::endl;
	}
	else {
		std::cerr << "No data received." << std::endl;
	}
	sqlite3_finalize(stmt);

	for (int i = 109; i >= 102; i--) {

		std::string copyQuery = "UPDATE chambres SET "
			"nom = (SELECT nom FROM chambres WHERE chambre = '" + std::to_string(i - 1) + "'), "
			"prenom = (SELECT prenom FROM chambres WHERE chambre = '" + std::to_string(i - 1) + "'), "
			"reserve = (SELECT reserve FROM chambres WHERE chambre = '" + std::to_string(i - 1) + "') "
			"WHERE chambre = '" + std::to_string(i) + "';";

		rc = sqlite3_exec(db, copyQuery.c_str(), nullptr, nullptr, &errorMessage);
	}


	// update the last one
	std::string copyQuery = "UPDATE chambres SET "
		"nom = '" + nom + "', "
		"prenom = '" + prenom + "', "
		"reserve = '" + reserve + "' "
		"WHERE chambre = '" + std::to_string(101) + "';";

	rc = sqlite3_exec(db, copyQuery.c_str(), nullptr, nullptr, &errorMessage);

	MessageBox::Show("Done!", "Succès");
	sqlite3_close(db);
}
void sortReservations(System::Windows::Forms::ComboBox^ comboBox, System::Windows::Forms::CheckBox^ checkBox1, System::Windows::Forms::RichTextBox^ richTextBox1) {
	richTextBox1->Text = "";

	if (comboBox->SelectedIndex == -1) {
		MessageBox::Show("Remplir option");
		return;
	}

	const char* dbPath = "database_hotel.db";
	sqlite3* db;
	sqlite3_stmt* stmt;


	int rc = sqlite3_open(dbPath, &db);
	if (rc) {
		MessageBox::Show("Couldn't open the database.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	String^ sortOption;
	std::string option;

	sortOption = comboBox->SelectedItem->ToString();

	msclr::interop::marshal_context context;
	option = context.marshal_as<std::string>(sortOption);


	std::string query;
	if (checkBox1->Checked) {
		query = "SELECT * FROM chambres ORDER BY " + option + " DESC;";
	}
	else {
		query = "SELECT * FROM chambres ORDER BY " + option + " ASC;";
	}

	const char* sqlQuery = query.c_str();

	// prepare SQL queryr
	rc = sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		MessageBox::Show("Couldn't prepare query", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		sqlite3_close(db);
		return;
	}

	// vars to receive results
	const char* col1;
	const char* col2;
	const char* col3;
	const char* col4;


	if (option == "chambre") {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			col1 = (const char*)sqlite3_column_text(stmt, 1); // chambre
			col2 = (const char*)sqlite3_column_text(stmt, 2); // nom
			col3 = (const char*)sqlite3_column_text(stmt, 3); // prenom
			col4 = (const char*)sqlite3_column_text(stmt, 4); // réservation

			richTextBox1->AppendText("----------------\n");
			String^ result = "Chambre " + gcnew String(col1);
			richTextBox1->AppendText(result + "\n");
			richTextBox1->AppendText("----------------\n");
			result = "Nom: " + gcnew String(col2);
			richTextBox1->AppendText(result + "\n");
			result = "Prénom: " + gcnew String(col3);
			richTextBox1->AppendText(result + "\n");
			richTextBox1->AppendText("Réservée: ");
			result = gcnew String(col4);
			if (gcnew String(col4) == "non") {
				richTextBox1->SelectionColor = System::Drawing::Color::Red;
				richTextBox1->AppendText(result + "\n\n");
			}
			else {
				richTextBox1->SelectionColor = System::Drawing::Color::Green;
				result = gcnew String(col4);
				richTextBox1->AppendText(result + "\n\n");
			}

			// default color
			richTextBox1->SelectionColor = System::Drawing::Color::Black;
		}
	}
	else if (option == "nom") {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			col1 = (const char*)sqlite3_column_text(stmt, 1); // chambre
			col2 = (const char*)sqlite3_column_text(stmt, 2); // nom
			col3 = (const char*)sqlite3_column_text(stmt, 3); // prenom
			col4 = (const char*)sqlite3_column_text(stmt, 4); // réservation

			richTextBox1->AppendText("----------------\n");
			String^ result = "Nom: " + gcnew String(col2);
			richTextBox1->AppendText(result + "\n");
			richTextBox1->AppendText("----------------\n");
			result = "Prénom: " + gcnew String(col3);
			richTextBox1->AppendText(result + "\n");
			result = "Chambre: " + gcnew String(col1);
			richTextBox1->AppendText(result + "\n");
			richTextBox1->AppendText("Réservée: ");
			result = gcnew String(col4);
			if (gcnew String(col4) == "non") {
				richTextBox1->SelectionColor = System::Drawing::Color::Red;
				richTextBox1->AppendText(result + "\n\n");
			}
			else {
				richTextBox1->SelectionColor = System::Drawing::Color::Green;
				result = gcnew String(col4);
				richTextBox1->AppendText(result + "\n\n");
			}

			// default color
			richTextBox1->SelectionColor = System::Drawing::Color::Black;
		}
	}

	// par prenom
	else {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			col1 = (const char*)sqlite3_column_text(stmt, 1); // chambre
			col2 = (const char*)sqlite3_column_text(stmt, 2); // nom
			col3 = (const char*)sqlite3_column_text(stmt, 3); // prenom
			col4 = (const char*)sqlite3_column_text(stmt, 4); // réservation

			richTextBox1->AppendText("----------------\n");
			String^ result = "Prénom: " + gcnew String(col3);
			richTextBox1->AppendText(result + "\n");
			richTextBox1->AppendText("----------------\n");
			result = "Nom: " + gcnew String(col2);
			richTextBox1->AppendText(result + "\n");
			result = "Chambre: " + gcnew String(col1);
			richTextBox1->AppendText(result + "\n");
			richTextBox1->AppendText("Réservée: ");
			result = gcnew String(col4);
			if (gcnew String(col4) == "non") {
				richTextBox1->SelectionColor = System::Drawing::Color::Red;
				richTextBox1->AppendText(result + "\n\n");
			}
			else {
				richTextBox1->SelectionColor = System::Drawing::Color::Green;
				result = gcnew String(col4);
				richTextBox1->AppendText(result + "\n\n");
			}

			// default color
			richTextBox1->SelectionColor = System::Drawing::Color::Black;
		}
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	comboBox->SelectedIndex = -1;
	checkBox1->Checked = false;
}
void showPercentage() {
	sqlite3* db;
	char* errorMessage = nullptr;
	sqlite3_stmt* stmt;

	int rc = sqlite3_open("database_hotel.db", &db);
	if (rc) {
		MessageBox::Show("Error opening database: " + gcnew String(sqlite3_errmsg(db)), "SQLite Error");
		return;
	}

	// check how many with reserve == 'oui'
	std::string countQuery = "SELECT COUNT(*) FROM chambres WHERE reserve = 'oui';";
	rc = sqlite3_prepare_v2(db, countQuery.c_str(), -1, &stmt, 0);
	if (rc != SQLITE_OK) {
		std::cerr << "Erro ao preparar a consulta: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return;
	}



	int countResult = 0;
	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		countResult = sqlite3_column_int(stmt, 0);
	}
	else {
		std::cerr << "Couldn't execute query: " << sqlite3_errmsg(db) << std::endl;
	}

	double formattedPercentage = countResult / 9.0 * 100;

	// convert to String^
	String^ formattedPercentageStr = formattedPercentage.ToString("0.##");
	MessageBox::Show("Pourcentage de chambres occupées: " + formattedPercentageStr + "%", "Statistique", MessageBoxButtons::OK, MessageBoxIcon::Information);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}
