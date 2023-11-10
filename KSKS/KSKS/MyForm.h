#include <Winsock2.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <msclr/marshal_cppstd.h>
#pragma comment(lib, "ws2_32.lib")

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;

struct Command {
    std::string name;
    std::vector<std::string> params;
};

struct Sprite {
    int index;
    int width;
    int height;
    std::vector<unsigned char> data;
};

std::vector<Sprite> sprites;


bool get_error = false;
int vibor_paint = 0;

int numberParam[6];
int have_param = 0;
std::string stringParam[3];
int have_param2 = 0;
int paint_paint = 0;


namespace KSKS {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    /// <summary>
    /// Сводка для MyForm
    /// </summary>


    public ref class MyForm : public System::Windows::Forms::Form
    {
    private:
        UdpClient^ udpServer;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Panel^ panel1;

           Timer^ timer;

           int port = 12345;
    private: System::Windows::Forms::Label^ label3;
    private: Bitmap^ mapaBitov;
    public:
        MyForm(void)
        {
            InitializeComponent();
            //
            //TODO: добавьте код конструктора
            //
            udpServer = gcnew UdpClient(port);
            udpServer->BeginReceive(gcnew AsyncCallback(this, &MyForm::ReceiveCallback), nullptr);
            mapaBitov = gcnew Bitmap(panel1->Width, panel1->Height);
        }
    private:

        void UpdateSystemTime(Object^ sender, EventArgs^ e)
        {
            // Получаем текущее системное время
            auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            struct tm timeInfo;
            localtime_s(&timeInfo, &now);

            // Форматируем время в строку
            String^ currentTime = gcnew String(asctime(&timeInfo));

            // Обновляем текст в Label
            label1->Text = currentTime;
        }

        void ReceiveCallback(IAsyncResult^ ar)
        {
            IPEndPoint^ endPoint = gcnew IPEndPoint(IPAddress::Any, port);
            array<Byte>^ receiveBytes = udpServer->EndReceive(ar, endPoint);
            String^ receivedMessage = Encoding::ASCII->GetString(receiveBytes);

            // Обработка полученного сообщения
            // Ваш код для обработки сообщения
            this->Invoke(gcnew Action<String^>(this, &MyForm::parsing_mes), receivedMessage);
            // Продолжаем прослушивать порт
            udpServer->BeginReceive(gcnew AsyncCallback(this, &MyForm::ReceiveCallback), nullptr);
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
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label1->Location = System::Drawing::Point(27, 400);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(304, 27);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Строка пустая";
            // 
            // panel1
            // 
            this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panel1->Location = System::Drawing::Point(27, 26);
            this->panel1->Name = L"panel1";
            this->panel1->Size = System::Drawing::Size(720, 370);
            this->panel1->TabIndex = 2;
            this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panel1_Paint);
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(773, 450);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->panel1);
            this->Controls->Add(this->label1);
            this->Name = L"MyForm";
            this->Text = L"MyForm";
            this->ResumeLayout(false);
            this->PerformLayout();

        }

        void DrawRoundedRectangle(Graphics^ g, Pen^ pen, int x, int y, int width, int height, int radius)
        {
            GraphicsPath^ path = gcnew GraphicsPath();

            System::Drawing::Rectangle rect = System::Drawing::Rectangle(x, y, width, height);

            int diameter = 2 * radius;
            System::Drawing::Rectangle arc = System::Drawing::Rectangle(rect.Location, System::Drawing::Size(diameter, diameter));

            path->AddArc(arc, 180, 90);
            arc.X = rect.Right - diameter;
            path->AddArc(arc, 270, 90);
            arc.Y = rect.Bottom - diameter;
            path->AddArc(arc, 0, 90);
            arc.X = rect.Left;
            path->AddArc(arc, 90, 90);

            path->CloseFigure();


            g->DrawPath(pen, path);

            delete path;
        }

        void FillRoundedRectangle(Graphics^ g, int x, int y, int width, int height, int radius, Color fillColor)
        {
            System::Drawing::Drawing2D::GraphicsPath^ path = gcnew System::Drawing::Drawing2D::GraphicsPath();
            System::Drawing::Rectangle rect = System::Drawing::Rectangle(x, y, width, height);
            int diameter = 2 * radius;
            System::Drawing::Rectangle arc = System::Drawing::Rectangle(rect.Location, System::Drawing::Size(diameter, diameter));
            path->AddArc(arc, 180, 90);
            arc.X = rect.Right - diameter;
            path->AddArc(arc, 270, 90);
            arc.Y = rect.Bottom - diameter;
            path->AddArc(arc, 0, 90);
            arc.X = rect.Left;
            path->AddArc(arc, 90, 90);

            path->CloseFigure();

            SolidBrush^ fillBrush = gcnew SolidBrush(fillColor);
            g->FillPath(fillBrush, path);

            delete path;
            delete fillBrush;
        }

        void DrawText2(Graphics^ g, String^ text, Color textColor, int x, int y, int fonte, int len)
        {
            System::Drawing::Font^ font;
            switch (fonte)
            {
            case 1:
                font = gcnew System::Drawing::Font("Arial", len);
                break;
            case 2:
                font = gcnew System::Drawing::Font("Times New Roman", len);
                break;
            case 3:
                font = gcnew System::Drawing::Font("Courier New", len);
                break;
            default:
                get_error = true;
                break;
            }
            System::Drawing::Brush^ brush = gcnew SolidBrush(textColor);
            g->DrawString(text, font, brush, x, y);
        }

        Color GetColor(std::string this_color)
        {
            if ("black" == this_color)
            {
                return Color::Black;
            }
            else if ("white" == this_color)
            {
                return Color::White;
            }
            else if ("red" == this_color)
            {
                return Color::Red;
            }
            else if ("blue" == this_color)
            {
                return Color::Blue;
            }
            else if ("green" == this_color)
            {
                return Color::Green;
            }
            else if ("orange" == this_color)
            {
                return Color::Orange;
            }
            else if ("yellow" == this_color)
            {
                return Color::Yellow;
            }
            else if ("cyan" == this_color)
            {
                return Color::Cyan;
            }
            else if ("brown" == this_color)
            {
                return Color::Brown;
            }
            else  if ("magenta" == this_color)
            {
                return Color::Magenta;
            }
            else if ("pink" == this_color)
            {
                return Color::Pink;
            }
            else if ("purple" == this_color)
            {
                return Color::Purple;
            }
            else  if ("gray" == this_color)
            {
                return Color::Gray;
            }
            else if ("lightgray" == this_color)
            {
                return Color::LightGray;
            }
            else  if ("darkgray" == this_color)
            {
                return Color::DarkGray;
            }
            else {
                return Color::White;
                get_error = true;
            }
        }

        void drawLetterA(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 20, y + 0);
            g->DrawLine(pen, x + 20, y + 0, x + 40, y + 100);
            g->DrawLine(pen, x + 5, y + 50, x + 40, y + 50);
        }
        void drawLetterB(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 0, y + 0, x + 40, y + 25);
            g->DrawLine(pen, x + 40, y + 25, x + 0, y + 50);

            g->DrawLine(pen, x + 0, y + 100, x + 40, y + 75);
            g->DrawLine(pen, x + 40, y + 75, x + 0, y + 50);

        }

        void drawLetterC(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 100);
            g->DrawLine(pen, x + 40, y + 0, x + 0, y + 0);
        }
        void drawLetterD(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 15, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 85, x + 0, y + 100);
            g->DrawLine(pen, x + 40, y + 85, x + 40, y + 15);
        }
        void drawLetterE(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 100);
            g->DrawLine(pen, x + 30, y + 50, x + 0, y + 50);
            g->DrawLine(pen, x + 40, y + 0, x + 0, y + 0);
        }
        void drawLetterF(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 50, x + 0, y + 50);
            g->DrawLine(pen, x + 40, y + 0, x + 0, y + 0);
        }
        void drawLetterG(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 100);
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 55);
            g->DrawLine(pen, x + 20, y + 55, x + 40, y + 55);
            g->DrawLine(pen, x + 40, y + 0, x + 0, y + 0);
        }
        void drawLetterH(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 0);
            g->DrawLine(pen, x + 40, y + 50, x + 0, y + 50);
        }
        void drawLetterI(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
        }
        void drawLetterJ(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 100);
        }
        void drawLetterK(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 0, y + 50, x + 40, y + 100);
            g->DrawLine(pen, x + 0, y + 50, x + 40, y + 0);
        }
        void drawLetterL(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x + 0, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 0, y + 100, x + 40, y + 100);
        }
        void drawLetterM(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 0);

            g->DrawLine(pen, x + 20, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 20, y + 100, x + 40, y + 0);
        }
        void drawLetterN(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 0);

            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 0);
        }
        void drawLetterO(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 100);
            g->DrawLine(pen, x + 40, y + 0, x + 0, y + 0);
        }
        void drawLetterP(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 0, y + 0, x + 40, y + 25);
            g->DrawLine(pen, x + 40, y + 25, x + 0, y + 50);
        }
        void drawLetterQ(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 80, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 0);
            g->DrawLine(pen, x + 40, y + 80, x + 0, y + 80);
            g->DrawLine(pen, x + 40, y + 0, x + 0, y + 0);
        }
        void drawLetterR(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 0, y + 0, x + 40, y + 25);
            g->DrawLine(pen, x + 40, y + 25, x + 0, y + 50);
            g->DrawLine(pen, x + 0, y + 50, x + 40, y + 100);
        }
        void drawLetterS(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 100);
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 50);
            g->DrawLine(pen, x + 40, y + 50, x + 0, y + 50);
            g->DrawLine(pen, x + 0, y + 50, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 0, x + 0, y + 0);
        }
        void drawLetterT(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x + 20, y + 100, x + 20, y + 0);
            g->DrawLine(pen, x + 0, y + 0, x + 40, y + 0);
        }
        void drawLetterU(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 100);
        }
        void drawLetterV(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 0, x + 20, y + 100);
            g->DrawLine(pen, x + 20, y + 100, x + 40, y + 0);
        }
        void drawLetterW(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 0);

            g->DrawLine(pen, x + 20, y + 0, x + 0, y + 100);
            g->DrawLine(pen, x + 20, y + 0, x + 40, y + 100);
        }
        void drawLetterX(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 40, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 0);
        }
        void drawLetterY(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x + 20, y + 50, x + 20, y + 100);
            g->DrawLine(pen, x + 20, y + 50, x + 0, y + 0);
            g->DrawLine(pen, x + 20, y + 50, x + 40, y + 0);
        }
        void drawLetterZ(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 0, x + 40, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 100);
            g->DrawLine(pen, x + 40, y + 0, x + 0, y + 100);
        }


        void drawImage(Graphics^ g, int x0, int y0, int w, int h, array<Color>^ DataIm)
        {
            for (int x = 0; x < w; x++)
            {
                for (int y = 0; y < h; y++)
                {
                    Color pixelColor = DataIm[x + y * w];
                    SolidBrush^ brush = gcnew SolidBrush(pixelColor);
                    g->FillRectangle(brush, x0 + x, y0 + y, 1, 1);
                }
            }
        }


        void HandleLoadSprite(int index, int width, int height, const std::vector<unsigned char>& data) {
            Sprite sprite;
            sprite.index = index;
            sprite.width = width;
            sprite.height = height;
            sprite.data = data;
            sprites.push_back(sprite);
        }
        void HandleShowSprite(int index, int x, int y) {
            for (const Sprite& sprite : sprites) {
                if (sprite.index == index) {
                    Bitmap^ spriteBitmap = gcnew Bitmap(sprite.width, sprite.height);

                    Graphics^ spriteGraphics = Graphics::FromImage(spriteBitmap);


                    System::Drawing::Rectangle destRect(x, y, sprite.width, sprite.height);
                    spriteGraphics->DrawImage(g, numberParam[0], numberParam[1], numberParam[2], numberParam[3], sprite.data);

                    Graphics^ panelGraphics = panel1->CreateGraphics();
                    panelGraphics->DrawImage(spriteBitmap, x, y);
                    delete spriteBitmap;
                    delete spriteGraphics;
                }
            }
        }

        void parsing_mes(String^ string_mes)
        {
            have_param = 0;
            have_param2 = 0;
            std::string buf_ar_mes = msclr::interop::marshal_as<std::string>(string_mes);
            Parsinge(buf_ar_mes);
            label1->Text = string_mes;

            if (get_error == false)
            {
                Color coloor = GetColor(stringParam[0]);

                Graphics^ g = Graphics::FromImage(mapaBitov);
                Pen^ pen = gcnew Pen(coloor, 2);
                SolidBrush^ brush = gcnew SolidBrush(coloor);

                if (paint_paint == 1)
                {
                    mapaBitov = gcnew Bitmap(panel1->Width, panel1->Height);
                    panel1->BackColor = coloor;
                    panel1->Invalidate();
                }

                if (paint_paint == 2) {
                    g->DrawLine(pen, numberParam[0], numberParam[1], numberParam[0] + 1, numberParam[1] + 1);

                }
                if (paint_paint == 3) {
                    g->DrawLine(pen, numberParam[0], numberParam[1], numberParam[2], numberParam[3]);
                }
                if (paint_paint == 4) {

                    g->DrawRectangle(pen, numberParam[0], numberParam[1], numberParam[2], numberParam[3]);
                }
                if (paint_paint == 5) {

                    g->FillRectangle(brush, numberParam[0], numberParam[1], numberParam[2], numberParam[3]);
                }
                if (paint_paint == 6) {

                    g->DrawEllipse(pen, numberParam[0], numberParam[1], numberParam[2], numberParam[3]);
                }
                if (paint_paint == 7) {

                    g->FillEllipse(brush, numberParam[0], numberParam[1], numberParam[2], numberParam[3]);
                }
                if (paint_paint == 8)
                {
                    g->DrawEllipse(pen, numberParam[0], numberParam[1], numberParam[2], numberParam[2]);
                }
                if (paint_paint == 9)
                {
                    g->FillEllipse(brush, numberParam[0], numberParam[1], numberParam[2], numberParam[2]);
                }
                if (paint_paint == 10)
                {
                    DrawRoundedRectangle(g, pen, numberParam[0], numberParam[1], numberParam[2], numberParam[3], numberParam[4]);
                }
                if (paint_paint == 11)
                {
                    FillRoundedRectangle(g, numberParam[0], numberParam[1], numberParam[2], numberParam[3], numberParam[4], coloor);
                }
                if (paint_paint == 12)
                {
                    String^ textToDraw = msclr::interop::marshal_as<String^>(stringParam[1]);

                    DrawText2(g, textToDraw, coloor, numberParam[0], numberParam[1], numberParam[2], numberParam[3]);
                }
                if (paint_paint == 13)
                {
                    array<Color>^ DataIm = gcnew array<Color>(numberParam[2] * numberParam[3]);

                    for (int i = 0; i < DataIm->Length; i++)
                    {
                        DataIm[i] = coloor;
                    }


                    drawImage(g, numberParam[0], numberParam[1], numberParam[2], numberParam[3], DataIm);
                }
                if (paint_paint == 15)
                {
                    HandleLoadSprite(numberParam[0], numberParam[1], numberParam[2], DataIm);
                }
                if (paint_paint == 16)
                {
                    HandleShowSprite(numberParam[0], numberParam[1], numberParam[2]);
                }
                if (paint_paint == 14)
                {
                    std::cout << "3";
                    std::string wordd = stringParam[1];
                    int x = numberParam[0], y = numberParam[1];
                    for (char letter : wordd) {
                        if (letter == 'A' || letter == 'a') {
                            std::cout << letter;
                            drawLetterA(x, y, g, pen);
                        }
                        else if (letter == 'B' || letter == 'b') {
                            drawLetterB(x, y, g, pen);
                        }
                        else if (letter == 'C' || letter == 'c') {
                            drawLetterC(x, y, g, pen);
                        }
                        else if (letter == 'D' || letter == 'd') {
                            drawLetterD(x, y, g, pen);
                        }
                        else if (letter == 'E' || letter == 'e') {
                            drawLetterE(x, y, g, pen);
                        }
                        else if (letter == 'F' || letter == 'f') {
                            drawLetterF(x, y, g, pen);
                        }
                        else if (letter == 'G' || letter == 'g') {
                            drawLetterG(x, y, g, pen);
                        }
                        else if (letter == 'H' || letter == 'h') {
                            drawLetterH(x, y, g, pen);
                        }
                        else if (letter == 'I' || letter == 'i') {
                            drawLetterI(x, y, g, pen);
                        }
                        else if (letter == 'J' || letter == 'j') {
                            drawLetterJ(x, y, g, pen);
                        }
                        else if (letter == 'K' || letter == 'k') {
                            drawLetterK(x, y, g, pen);
                        }
                        else if (letter == 'L' || letter == 'l') {
                            drawLetterL(x, y, g, pen);
                        }
                        else if (letter == 'M' || letter == 'm') {
                            drawLetterM(x, y, g, pen);
                        }
                        else if (letter == 'N' || letter == 'n') {
                            drawLetterN(x, y, g, pen);
                        }
                        else if (letter == 'O' || letter == 'o') {
                            drawLetterO(x, y, g, pen);
                        }
                        else if (letter == 'P' || letter == 'p') {
                            drawLetterP(x, y, g, pen);
                        }
                        else if (letter == 'Q' || letter == 'q') {
                            drawLetterQ(x, y, g, pen);
                        }
                        else if (letter == 'R' || letter == 'r') {
                            drawLetterR(x, y, g, pen);
                        }
                        else if (letter == 'S' || letter == 's') {
                            drawLetterS(x, y, g, pen);
                        }
                        else if (letter == 'T' || letter == 't') {
                            drawLetterT(x, y, g, pen);
                        }
                        else if (letter == 'U' || letter == 'u') {
                            drawLetterU(x, y, g, pen);
                        }
                        else if (letter == 'V' || letter == 'v') {
                            drawLetterV(x, y, g, pen);
                        }
                        else if (letter == 'W' || letter == 'w') {
                            drawLetterW(x, y, g, pen);
                        }
                        else if (letter == 'X' || letter == 'x') {
                            drawLetterX(x, y, g, pen);
                        }
                        else if (letter == 'Y' || letter == 'y') {
                            drawLetterY(x, y, g, pen);
                        }
                        else if (letter == 'Z' || letter == 'z') {
                            drawLetterZ(x, y, g, pen);
                        }
                        x += 60;
                    }
                }


                delete g;
                delete pen;
                delete brush;

                panel1->Invalidate();
                paint_paint = 0;
            }
            else {
                label1->Text = "Ошибка! Вы ввели неверную команду";
            }
        }


        Command Parsinge(const std::string& comanda_string) {
            Command command;

            int thisNumP;

            std::istringstream stream_string(comanda_string);
            std::string this_word;
            stream_string >> command.name;

            int j = 0;
            int i = 0;
            while (stream_string >> this_word) {
                if (this_word == ":")
                {
                    break;
                }

                command.name += " " + this_word;
            }

            if (command.name == "clear display") {
                get_error = false;
                vibor_paint = 1;
                paint_paint = 1;
            }
            else if (command.name == "draw pixel") {
                vibor_paint = 2;
                paint_paint = 2;
                get_error = false;
            }
            else if (command.name == "draw line") {
                vibor_paint = 5;
                paint_paint = 3;
                get_error = false;
            }
            else if (command.name == "draw rectangle")
            {
                vibor_paint = 10;
                paint_paint = 4;
                get_error = false;
            }
            else if (command.name == "fill rectangle") {
                vibor_paint = 15;
                paint_paint = 5;
                get_error = false;
            }
            else if (command.name == "draw ellipse") {
                vibor_paint = 20;
                paint_paint = 6;
                get_error = false;
            }
            else if (command.name == "fill ellipse")
            {
                paint_paint = 7;
                vibor_paint = 25;
                get_error = false;
            }
            else if (command.name == "draw circle")
            {
                paint_paint = 8;
                vibor_paint = 30;
                get_error = false;
            }
            else if (command.name == "fill circle")
            {
                paint_paint = 9;
                vibor_paint = 34;
                get_error = false;
            }
            else if (command.name == "draw rounded rectangle")
            {
                paint_paint = 10;
                vibor_paint = 38;
                get_error = false;
            }
            else if (command.name == "fill rounded rectangle")
            {
                paint_paint = 11;
                vibor_paint = 44;
                get_error = false;
            }
            else if (command.name == "draw text")
            {
                paint_paint = 12;
                vibor_paint = 50;
                get_error = false;
            }
            else if (command.name == "draw image")
            {
                paint_paint = 13;
                vibor_paint = 56;
                get_error = false;
            }
            else if (command.name == "letter line")
            {
                std::cout << "1";
                paint_paint = 14;
                vibor_paint = 61;
                get_error = false;
            }
            else if (command.name == "load sprite")
            {
                std::cout << "1";
                paint_paint = 15;
                vibor_paint = 65;
                get_error = false;
            }
            else if (command.name == "show sprite")
            {
                std::cout << "1";
                paint_paint = 16;
                vibor_paint = 69;
                get_error = false;
            }
            else {
                get_error = true;
            }


            if (!get_error)
            {
                while (stream_string >> this_word) {
                    switch (vibor_paint)
                    {
                    case 1: case 4: case 9: case 14: case 19: case 24: case 29: case 33:
                    case 37: case 43: case 49: case 52: case 55: case 60: case 63: case 64:
                    case 68:
                        command.params.push_back(this_word);
                        try {
                            thisNumP = std::stoi(this_word);
                        }
                        catch (const std::invalid_argument& e) {
                            get_error = false;
                            stringParam[j] = this_word;
                            have_param2++;
                            j++;
                            if (vibor_paint != 52)
                            {
                                std::cout << "2";
                                if (vibor_paint != 63)
                                {
                                    std::cout << "7";
                                    return command;
                                }
                            }
                            else {
                            }
                            vibor_paint++;
                        }
                        get_error = true;
                        break;

                    case 2: case 3: case 5: case 6: case 7: case 8: case 10: case 11: case 12: case 13:
                    case 15: case 16: case 17: case 18: case 20: case 21: case 22: case 23:
                    case 25: case 26: case 27: case 28: case 30: case 31: case 32: case 34:
                    case 35: case 36: case 38: case 39: case 40: case 41: case 42: case 44:
                    case 45: case 46: case 47: case 48: case 50: case 51: case 53: case 54:
                    case 56: case 57: case 58: case 59: case 61: case 62: case 65: case 66: case 67:
                    case 69: case 70: case 71:
                        std::cout << "4";
                        command.params.push_back(this_word);
                        try {
                            thisNumP = std::stoi(this_word);
                        }
                        catch (const std::invalid_argument& e) {
                            get_error = true;
                            return command;
                        }
                        get_error = false;
                        vibor_paint++;
                        numberParam[i] = thisNumP;
                        have_param++;
                        i++;
                        break;
                        ///
                    }
                }
                get_error = true;
                return command;
            }
            else {
                return command;
            }
        }

        void mes_get(String^ message) {

        }
#pragma endregion
    private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
        e->Graphics->DrawImage(mapaBitov, 0, 0);
    }
    };
}
