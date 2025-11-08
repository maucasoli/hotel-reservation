#pragma once

#include "functions.h"
#include "sqlite3.h"

namespace Hotel {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ModifyNom
	/// </summary>
	public ref class ModifyNom : public System::Windows::Forms::Form
	{
	public:
		ModifyNom(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ModifyNom()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel2;
	protected:
	private: System::Windows::Forms::TextBox^ txtPrenom;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ComboBox^ comboBox;
	private: System::Windows::Forms::Button^ btnSend;
	private: System::Windows::Forms::Button^ btnReturn;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::TextBox^ txtNom;
	private: System::Windows::Forms::Label^ label1;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ModifyNom::typeid));
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->txtPrenom = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBox = (gcnew System::Windows::Forms::ComboBox());
			this->btnSend = (gcnew System::Windows::Forms::Button());
			this->btnReturn = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->txtNom = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// panel2
			// 
			this->panel2->Location = System::Drawing::Point(50, 321);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(200, 2);
			this->panel2->TabIndex = 22;
			// 
			// txtPrenom
			// 
			this->txtPrenom->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->txtPrenom->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txtPrenom->ForeColor = System::Drawing::Color::White;
			this->txtPrenom->Location = System::Drawing::Point(50, 301);
			this->txtPrenom->Name = L"txtPrenom";
			this->txtPrenom->Size = System::Drawing::Size(200, 22);
			this->txtPrenom->TabIndex = 28;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(46, 275);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(77, 23);
			this->label3->TabIndex = 27;
			this->label3->Text = L"Prénom";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(46, 116);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(88, 23);
			this->label2->TabIndex = 26;
			this->label2->Text = L"Chambre";
			// 
			// comboBox
			// 
			this->comboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox->FormattingEnabled = true;
			this->comboBox->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
				L"101", L"102", L"103", L"104", L"105", L"106",
					L"107", L"108", L"109"
			});
			this->comboBox->Location = System::Drawing::Point(141, 116);
			this->comboBox->Name = L"comboBox";
			this->comboBox->Size = System::Drawing::Size(121, 31);
			this->comboBox->TabIndex = 25;
			// 
			// btnSend
			// 
			this->btnSend->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnSend->FlatAppearance->BorderColor = System::Drawing::Color::Silver;
			this->btnSend->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnSend->ForeColor = System::Drawing::Color::White;
			this->btnSend->Location = System::Drawing::Point(12, 452);
			this->btnSend->Name = L"btnSend";
			this->btnSend->Size = System::Drawing::Size(150, 36);
			this->btnSend->TabIndex = 24;
			this->btnSend->Text = L"Modifier";
			this->btnSend->UseVisualStyleBackColor = false;
			this->btnSend->Click += gcnew System::EventHandler(this, &ModifyNom::btnSend_Click);
			// 
			// btnReturn
			// 
			this->btnReturn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnReturn->FlatAppearance->BorderColor = System::Drawing::Color::Silver;
			this->btnReturn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnReturn->ForeColor = System::Drawing::Color::White;
			this->btnReturn->Location = System::Drawing::Point(168, 452);
			this->btnReturn->Name = L"btnReturn";
			this->btnReturn->Size = System::Drawing::Size(150, 36);
			this->btnReturn->TabIndex = 23;
			this->btnReturn->Text = L"Retourner";
			this->btnReturn->UseVisualStyleBackColor = false;
			this->btnReturn->Click += gcnew System::EventHandler(this, &ModifyNom::btnReturn_Click);
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(50, 229);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(200, 2);
			this->panel1->TabIndex = 21;
			// 
			// txtNom
			// 
			this->txtNom->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->txtNom->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txtNom->ForeColor = System::Drawing::Color::White;
			this->txtNom->Location = System::Drawing::Point(50, 209);
			this->txtNom->Name = L"txtNom";
			this->txtNom->Size = System::Drawing::Size(200, 22);
			this->txtNom->TabIndex = 20;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(46, 183);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(52, 23);
			this->label1->TabIndex = 19;
			this->label1->Text = L"Nom";
			// 
			// ModifyNom
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(600, 500);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->txtPrenom);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->comboBox);
			this->Controls->Add(this->btnSend);
			this->Controls->Add(this->btnReturn);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->txtNom);
			this->Controls->Add(this->label1);
			this->Font = (gcnew System::Drawing::Font(L"Georgia", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->MaximumSize = System::Drawing::Size(600, 500);
			this->MinimumSize = System::Drawing::Size(600, 500);
			this->Name = L"ModifyNom";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"ModifyNom";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// Button: Modify
	private: System::Void btnSend_Click(System::Object^ sender, System::EventArgs^ e) {
		modifyNom(comboBox, txtNom, txtPrenom);
	}
		   // Button: Return
	private: System::Void btnReturn_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}



	};
}
