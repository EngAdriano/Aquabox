program Aquabox;

uses
  System.StartUpCopy,
  FMX.Forms,
  untInicial in 'untInicial.pas' {Form1};

{$R *.res}

begin
  Application.Initialize;
  Application.FormFactor.Orientations := [TFormOrientation.Portrait];
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
