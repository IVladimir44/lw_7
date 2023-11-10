#include <Winsock2.h>
#include <iostream>
#include <vector>
#pragma comment(lib, "ws2_32.lib")

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;

namespace KSKSClient {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
		UdpClient^ udpClient;
		int serverPort = 12345;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button2;


		   String^ serverIPAddress = "127.0.0.1";
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			udpClient = gcnew UdpClient();
		}

	private:
		void SendMessage(String^ message)
		{
			array<Byte>^ sendBytes = Encoding::ASCII->GetBytes(message);
			udpClient->Send(sendBytes, sendBytes->Length, serverIPAddress, serverPort);
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
		void SendMessageButton_Click(Object^ sender, EventArgs^ e)
		{
			String^ messageToSend = "Привет, сервер!";
			SendMessage(messageToSend);
		}

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(582, 142);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(137, 53);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Отправить";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(12, 142);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(416, 55);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Введите команду";
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(12, 66);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(707, 38);
			this->textBox1->TabIndex = 3;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(434, 142);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(137, 53);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Рандомная команда";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(750, 221);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		void SendImageToServer(Bitmap^ image)
		{
			int width = image->Width;
			int height = image->Height;
			array<Color>^ pixelData = gcnew array<Color>(width * height);

			for (int x = 0; x < width; x++)
			{
				for (int y = 0; y < height; y++)
				{
					pixelData[x + y * width] = image->GetPixel(x, y);
				}
			}


			array<Byte>^ imageData = gcnew array<Byte>(width * height * 4);

			for (int i = 0; i < width * height; i++)
			{
				imageData[i * 4] = pixelData[i].A;
				imageData[i * 4 + 1] = pixelData[i].R;
				imageData[i * 4 + 2] = pixelData[i].G;
				imageData[i * 4 + 3] = pixelData[i].B;
			}

			UdpClient^ udpClient = gcnew UdpClient("127.0.0.1", 12345);
			IPEndPoint^ endPoint = gcnew IPEndPoint(IPAddress::Parse("127.0.0.1"), 12345);

			udpClient->Send(imageData, imageData->Length, endPoint);
			udpClient->Close();
		}


#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ buf_com = textBox1->Text;
		std::vector<unsigned char> imagePixels;
		SendMessage(buf_com);
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		SendMessage("random");
	}
	};
}
