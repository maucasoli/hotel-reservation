#pragma once

#include <iostream>
#include "functions.h"

#include "Create.h"
#include "Delete.h"
#include "ModifyNom.h"
#include "ModifyChambre.h"
#include "Display.h"
#include "Search.h"
#include "Sort.h"


namespace Hotel {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Main
	/// </summary>
	public ref class Main : public System::Windows::Forms::Form
	{
	public:
		Main(void)
		{

			InitializeComponent();

			// Create database and table if not exists
			startDatabase();


			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Main()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnCreate;
	private: System::Windows::Forms::Button^ btnDelete;
	private: System::Windows::Forms::Button^ btnModifyName;
	private: System::Windows::Forms::Button^ btnModifyRoom;
	private: System::Windows::Forms::Button^ btnDisplay;
	private: System::Windows::Forms::Button^ btnSearch;
	private: System::Windows::Forms::Button^ btnChange;
	private: System::Windows::Forms::Button^ btnSort;
	private: System::Windows::Forms::Button^ btnQuit;
	private: System::Windows::Forms::Button^ btnStat;


	protected:


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Main::typeid));
			this->btnCreate = (gcnew System::Windows::Forms::Button());
			this->btnDelete = (gcnew System::Windows::Forms::Button());
			this->btnModifyName = (gcnew System::Windows::Forms::Button());
			this->btnModifyRoom = (gcnew System::Windows::Forms::Button());
			this->btnDisplay = (gcnew System::Windows::Forms::Button());
			this->btnSearch = (gcnew System::Windows::Forms::Button());
			this->btnChange = (gcnew System::Windows::Forms::Button());
			this->btnSort = (gcnew System::Windows::Forms::Button());
			this->btnQuit = (gcnew System::Windows::Forms::Button());
			this->btnStat = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnCreate
			// 
			this->btnCreate->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnCreate->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->btnCreate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnCreate->ForeColor = System::Drawing::Color::White;
			this->btnCreate->Location = System::Drawing::Point(12, 72);
			this->btnCreate->Name = L"btnCreate";
			this->btnCreate->Size = System::Drawing::Size(252, 32);
			this->btnCreate->TabIndex = 0;
			this->btnCreate->Text = L"Creer une réservation";
			this->btnCreate->UseVisualStyleBackColor = false;
			this->btnCreate->Click += gcnew System::EventHandler(this, &Main::button1_Click);
			// 
			// btnDelete
			// 
			this->btnDelete->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnDelete->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->btnDelete->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnDelete->ForeColor = System::Drawing::Color::White;
			this->btnDelete->Location = System::Drawing::Point(12, 110);
			this->btnDelete->Name = L"btnDelete";
			this->btnDelete->Size = System::Drawing::Size(252, 32);
			this->btnDelete->TabIndex = 1;
			this->btnDelete->Text = L"Annuler une réservation";
			this->btnDelete->UseVisualStyleBackColor = false;
			this->btnDelete->Click += gcnew System::EventHandler(this, &Main::btnDelete_Click);
			// 
			// btnModifyName
			// 
			this->btnModifyName->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnModifyName->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->btnModifyName->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnModifyName->ForeColor = System::Drawing::Color::White;
			this->btnModifyName->Location = System::Drawing::Point(12, 148);
			this->btnModifyName->Name = L"btnModifyName";
			this->btnModifyName->Size = System::Drawing::Size(252, 32);
			this->btnModifyName->TabIndex = 2;
			this->btnModifyName->Text = L"Modifier nom, prénom";
			this->btnModifyName->UseVisualStyleBackColor = false;
			this->btnModifyName->Click += gcnew System::EventHandler(this, &Main::button2_Click);
			// 
			// btnModifyRoom
			// 
			this->btnModifyRoom->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnModifyRoom->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->btnModifyRoom->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnModifyRoom->ForeColor = System::Drawing::Color::White;
			this->btnModifyRoom->Location = System::Drawing::Point(12, 186);
			this->btnModifyRoom->Name = L"btnModifyRoom";
			this->btnModifyRoom->Size = System::Drawing::Size(252, 32);
			this->btnModifyRoom->TabIndex = 3;
			this->btnModifyRoom->Text = L"Modifier la chambre";
			this->btnModifyRoom->UseVisualStyleBackColor = false;
			this->btnModifyRoom->Click += gcnew System::EventHandler(this, &Main::btnModifyRoom_Click);
			// 
			// btnDisplay
			// 
			this->btnDisplay->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnDisplay->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->btnDisplay->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnDisplay->ForeColor = System::Drawing::Color::White;
			this->btnDisplay->Location = System::Drawing::Point(12, 224);
			this->btnDisplay->Name = L"btnDisplay";
			this->btnDisplay->Size = System::Drawing::Size(252, 32);
			this->btnDisplay->TabIndex = 4;
			this->btnDisplay->Text = L"Montrer les réservations";
			this->btnDisplay->UseVisualStyleBackColor = false;
			this->btnDisplay->Click += gcnew System::EventHandler(this, &Main::button4_Click);
			// 
			// btnSearch
			// 
			this->btnSearch->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnSearch->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->btnSearch->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnSearch->ForeColor = System::Drawing::Color::White;
			this->btnSearch->Location = System::Drawing::Point(12, 262);
			this->btnSearch->Name = L"btnSearch";
			this->btnSearch->Size = System::Drawing::Size(252, 32);
			this->btnSearch->TabIndex = 5;
			this->btnSearch->Text = L"Trouver une réservation";
			this->btnSearch->UseVisualStyleBackColor = false;
			this->btnSearch->Click += gcnew System::EventHandler(this, &Main::btnSearch_Click);
			// 
			// btnChange
			// 
			this->btnChange->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnChange->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->btnChange->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnChange->ForeColor = System::Drawing::Color::White;
			this->btnChange->Location = System::Drawing::Point(12, 300);
			this->btnChange->Name = L"btnChange";
			this->btnChange->Size = System::Drawing::Size(252, 32);
			this->btnChange->TabIndex = 6;
			this->btnChange->Text = L"Échanger les réservations";
			this->btnChange->UseVisualStyleBackColor = false;
			this->btnChange->Click += gcnew System::EventHandler(this, &Main::btnChange_Click);
			// 
			// btnSort
			// 
			this->btnSort->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnSort->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->btnSort->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnSort->ForeColor = System::Drawing::Color::White;
			this->btnSort->Location = System::Drawing::Point(12, 338);
			this->btnSort->Name = L"btnSort";
			this->btnSort->Size = System::Drawing::Size(252, 32);
			this->btnSort->TabIndex = 7;
			this->btnSort->Text = L"Trier les réservations";
			this->btnSort->UseVisualStyleBackColor = false;
			this->btnSort->Click += gcnew System::EventHandler(this, &Main::btnSort_Click);
			// 
			// btnQuit
			// 
			this->btnQuit->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnQuit->FlatAppearance->BorderColor = System::Drawing::Color::Silver;
			this->btnQuit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnQuit->ForeColor = System::Drawing::Color::White;
			this->btnQuit->Location = System::Drawing::Point(12, 456);
			this->btnQuit->Name = L"btnQuit";
			this->btnQuit->Size = System::Drawing::Size(252, 32);
			this->btnQuit->TabIndex = 9;
			this->btnQuit->Text = L"Quitter";
			this->btnQuit->UseVisualStyleBackColor = false;
			this->btnQuit->Click += gcnew System::EventHandler(this, &Main::btnQuit_Click);
			// 
			// btnStat
			// 
			this->btnStat->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnStat->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->btnStat->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnStat->ForeColor = System::Drawing::Color::White;
			this->btnStat->Location = System::Drawing::Point(12, 376);
			this->btnStat->Name = L"btnStat";
			this->btnStat->Size = System::Drawing::Size(252, 32);
			this->btnStat->TabIndex = 10;
			this->btnStat->Text = L"Statistique";
			this->btnStat->UseVisualStyleBackColor = false;
			this->btnStat->Click += gcnew System::EventHandler(this, &Main::btnStat_Click);
			// 
			// Main
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(600, 500);
			this->Controls->Add(this->btnStat);
			this->Controls->Add(this->btnQuit);
			this->Controls->Add(this->btnSort);
			this->Controls->Add(this->btnChange);
			this->Controls->Add(this->btnSearch);
			this->Controls->Add(this->btnDisplay);
			this->Controls->Add(this->btnModifyRoom);
			this->Controls->Add(this->btnModifyName);
			this->Controls->Add(this->btnDelete);
			this->Controls->Add(this->btnCreate);
			this->Font = (gcnew System::Drawing::Font(L"Georgia", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximumSize = System::Drawing::Size(600, 500);
			this->MinimumSize = System::Drawing::Size(600, 500);
			this->Name = L"Main";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Main";
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::Main_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::Main_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Main::Main_MouseUp);
			this->ResumeLayout(false);

		}

#pragma endregion

		// Button: Create reservation
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		Create^ formCreate = gcnew Create();
		formCreate->Show();
	}
		   // Button: Delete reservation
	private: System::Void btnDelete_Click(System::Object^ sender, System::EventArgs^ e) {
		Delete^ formDelete = gcnew Delete();
		formDelete->Show();
	}
		   // Button: Modify nom, prenom
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		ModifyNom^ formModifyNom = gcnew ModifyNom();
		formModifyNom->Show();
	}
		   // Button: Modify room 
	private: System::Void btnModifyRoom_Click(System::Object^ sender, System::EventArgs^ e) {
		ModifyChambre^ formModifyChambre = gcnew ModifyChambre();
		formModifyChambre->Show();
	}
		   // Button: Display reservations
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		Display^ formDisplay = gcnew Display();
		formDisplay->Show();
	}
		   // Button: Search reservation
	private: System::Void btnSearch_Click(System::Object^ sender, System::EventArgs^ e) {
		Search^ formSearch = gcnew Search();
		formSearch->Show();
	}
		   // Button: Echanger reservations
	private: System::Void btnChange_Click(System::Object^ sender, System::EventArgs^ e) {
		echangerReservations();
	}
		   // Button: Sort reservations
	private: System::Void btnSort_Click(System::Object^ sender, System::EventArgs^ e) {
		Sort^ formSort = gcnew Sort();
		formSort->Show();
	}

		   // Button: Statistics
	private: System::Void btnStat_Click(System::Object^ sender, System::EventArgs^ e) {
		showPercentage();
	}

		   // Button: Quit application
	private: System::Void btnQuit_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();
	}



		   // Move application window
		   bool dragging;
		   Point offset;
	private: System::Void Main_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		dragging = true;
		offset.X = e->X;
		offset.Y = e->Y;
	}
	private: System::Void Main_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (dragging) {
			Point currentScreenPosition = PointToScreen(Point(e->X, e->Y));
			Location = Point(currentScreenPosition.X - offset.X, currentScreenPosition.Y - offset.Y);
		}
	}
	private: System::Void Main_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		dragging = false;
	}

	};
}
