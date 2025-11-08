#pragma once


void startDatabase();
void createReservation(System::Windows::Forms::ComboBox^ comboBox, System::Windows::Forms::TextBox^ txtNom, System::Windows::Forms::TextBox^ txtPrenom);
void deleteReservation(System::Windows::Forms::ComboBox^ comboBox, System::Windows::Forms::TextBox^ txtNom, System::Windows::Forms::TextBox^ txtPrenom);
void modifyNom(System::Windows::Forms::ComboBox^ comboBox, System::Windows::Forms::TextBox^ txtNom, System::Windows::Forms::TextBox^ txtPrenom);
void modifyChambre(System::Windows::Forms::ComboBox^ comboBox, System::Windows::Forms::ComboBox^ comboBoxNew, System::Windows::Forms::TextBox^ txtNom, System::Windows::Forms::TextBox^ txtPrenom);
void displayReservations(System::Windows::Forms::RichTextBox^ richTextBox1);
bool confirmation(); // in the display form
void eraseTable(); // in the display form
void searchReservation(System::Windows::Forms::ComboBox^ comboBox, System::Windows::Forms::TextBox^ txtNom, System::Windows::Forms::TextBox^ txtPrenom, System::Windows::Forms::RichTextBox^ richTextBox1);
void echangerReservations();
void sortReservations(System::Windows::Forms::ComboBox^ comboBox, System::Windows::Forms::CheckBox^ checkBox1, System::Windows::Forms::RichTextBox^ richTextBox1);
void showPercentage();
