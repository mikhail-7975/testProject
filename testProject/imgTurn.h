#pragma once

//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Imaging.GIFImg.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:    // IDE-managed Components
	TImage *ImageSource;
	TImage *ImageDest;
	TButton *ButtonRotate;
	TLabeledEdit *LEangle;
	TTimer *Timer1;
	TShape *Shape;
	void __fastcall ButtonRotateClick(TObject *Sender);
	void __fastcall LEangleKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Timer1Timer(TObject *Sender);
private:    // User declarations
public:     // User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif