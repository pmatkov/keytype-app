object DataModule2: TDataModule2
  Height = 209
  Width = 313
  object IdTCPServer: TIdTCPServer
    Bindings = <
      item
        IP = '0.0.0.0'
        Port = 6001
      end>
    DefaultPort = 6001
    OnConnect = IdTCPServerConnect
    OnDisconnect = IdTCPServerDisconnect
    OnExecute = IdTCPServerExecute
    Left = 87
    Top = 81
  end
  object IdUDPServer: TIdUDPServer
    Bindings = <
      item
        IP = '0.0.0.0'
        Port = 6501
      end>
    DefaultPort = 6501
    OnUDPRead = IdUDPServerUDPRead
    Left = 183
    Top = 84
  end
end
