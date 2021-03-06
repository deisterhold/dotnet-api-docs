// <Snippet1>

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

using namespace System;
using namespace System::IO;
using namespace System::Drawing;
using namespace System::Drawing::Printing;
using namespace System::Windows::Forms;


public ref class PrintingExample
{
private:
   Font^ printFont;
   StreamReader^ streamToPrint;
   static String^ filePath;

public:
   PrintingExample()
   {
      Printing();
   }


private:

   // The PrintPage event is raised for each page to be printed.
   void pd_PrintPage( Object^ /*sender*/, PrintPageEventArgs^ ev )
   {
      float linesPerPage = 0;
      float yPos = 0;
      int count = 0;
      float leftMargin = (float)ev->MarginBounds.Left;
      float topMargin = (float)ev->MarginBounds.Top;
      String^ line = nullptr;
      
      // Calculate the number of lines per page.
      linesPerPage = ev->MarginBounds.Height / printFont->GetHeight( ev->Graphics );
      
      // Iterate over the file, printing each line.
      while ( count < linesPerPage && ((line = streamToPrint->ReadLine()) != nullptr) )
      {
         yPos = topMargin + (count * printFont->GetHeight( ev->Graphics ));
         ev->Graphics->DrawString( line, printFont, Brushes::Black, leftMargin, yPos, gcnew StringFormat );
         count++;
      }

      
      // If more lines exist, print another page.
      if ( line != nullptr )
            ev->HasMorePages = true;
      else
            ev->HasMorePages = false;
   }


public:

   // Print the file.
   void Printing()
   {
      try
      {
         streamToPrint = gcnew StreamReader( filePath );
         try
         {
            printFont = gcnew Font( "Arial",10 );
            PrintDocument^ pd = gcnew PrintDocument;
            pd->PrintPage += gcnew PrintPageEventHandler( this, &PrintingExample::pd_PrintPage );
            
            // Print the document.
            pd->Print();
         }
         finally
         {
            streamToPrint->Close();
         }

      }
      catch ( Exception^ ex ) 
      {
         MessageBox::Show( ex->Message );
      }

   }

   static void Main()
   {
      array<String^>^args = Environment::GetCommandLineArgs();
      String^ sampleName = args[ 0 ];
      if ( args->Length != 2 )
      {
         Console::WriteLine( "Usage: {0} <file path>", sampleName );
         return;
      }

      filePath = args[ 1 ];
      gcnew PrintingExample;
   }

};

int main()
{
   PrintingExample::Main();
}

// </Snippet1>
