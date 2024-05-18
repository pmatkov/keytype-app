object DataModule1: TDataModule1
  Height = 480
  Width = 640
  object MySQLDBConnection: TFDConnection
    Params.Strings = (
      'Database=keytype'
      'User_Name=root'
      'Password=12345'
      'Server=127.0.0.1'
      'DriverID=MySQL')
    Connected = True
    Left = 108
    Top = 225
  end
  object TCourses: TFDTable
    Active = True
    IndexFieldNames = 'id'
    Connection = MySQLDBConnection
    ResourceOptions.AssignedValues = [rvEscapeExpand]
    TableName = 'keytype.courses'
    Left = 279
    Top = 216
    object TCoursesid: TFDAutoIncField
      FieldName = 'id'
      Origin = 'id'
      ReadOnly = True
    end
    object TCoursesname: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'name'
      Origin = '`name`'
      Size = 30
    end
    object TCoursesdescription: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'description'
      Origin = 'description'
      Size = 255
    end
    object TCoursesdifficulty: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'difficulty'
      Origin = 'difficulty'
    end
    object TCoursesgoal: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'goal'
      Origin = 'goal'
      Size = 30
    end
    object TCoursesgoalValue: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'goalValue'
      Origin = 'goalValue'
    end
    object TCourseslanguage: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'language'
      Origin = 'language'
      Size = 30
    end
  end
  object TLessons: TFDTable
    Active = True
    OnCalcFields = TLessonsCalcFields
    IndexFieldNames = 'idCourses'
    MasterSource = DCourses
    MasterFields = 'id'
    Connection = MySQLDBConnection
    FormatOptions.AssignedValues = [fvSortLocale, fvSortOptions]
    ResourceOptions.AssignedValues = [rvEscapeExpand]
    TableName = 'keytype.lessons'
    Left = 343
    Top = 222
    object TLessonsid: TFDAutoIncField
      FieldName = 'id'
      Origin = 'id'
      ReadOnly = True
    end
    object TLessonsidCourses: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'idCourses'
      Origin = 'idCourses'
    end
    object TLessonsCourseName: TStringField
      DisplayWidth = 20
      FieldKind = fkLookup
      FieldName = 'courseName'
      LookupDataSet = TCourses
      LookupKeyFields = 'id'
      LookupResultField = 'name'
      KeyFields = 'idCourses'
      Lookup = True
    end
    object TLessonsname: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'name'
      Origin = '`name`'
      Size = 50
    end
    object TLessonsinstructions: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'instructions'
      Origin = 'instructions'
      Size = 255
    end
    object TLessonscharacters: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'characters'
      Origin = 'characters'
      Size = 50
    end
    object TLessonswordCount: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'wordCount'
      Origin = 'wordCount'
    end
    object TLessonscharCount: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'charCount'
      Origin = 'charCount'
    end
    object TLessonsAvgChars: TFloatField
      FieldKind = fkCalculated
      FieldName = 'avgChars'
      Calculated = True
    end
    object TLessonsdateModified: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'dateModified'
      Origin = 'dateModified'
    end
  end
  object DCourses: TDataSource
    DataSet = TCourses
    Left = 267
    Top = 291
  end
  object DLessons: TDataSource
    DataSet = TLessons
    Left = 336
    Top = 294
  end
  object DUsers: TDataSource
    DataSet = TUsers
    Left = 210
    Top = 288
  end
  object TUsers: TFDTable
    Active = True
    IndexFieldNames = 'id'
    Connection = MySQLDBConnection
    ResourceOptions.AssignedValues = [rvEscapeExpand]
    TableName = 'keytype.users'
    Left = 219
    Top = 213
    object TUsersid: TFDAutoIncField
      FieldName = 'id'
      Origin = 'id'
      ReadOnly = True
    end
    object TUsersusername: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'username'
      Origin = 'username'
    end
    object TUserspassword: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'password'
      Origin = '`password`'
      Size = 255
    end
    object TUserssalt: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'salt'
      Origin = 'salt'
      Size = 255
    end
    object TUsersname: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'name'
      Origin = '`name`'
    end
    object TUserssurname: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'surname'
      Origin = 'surname'
    end
    object TUsersemail: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'email'
      Origin = 'email'
    end
    object TUsersage: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'age'
      Origin = 'age'
    end
    object TUsersprofileImage: TBlobField
      AutoGenerateValue = arDefault
      FieldName = 'profileImage'
      Origin = 'profileImage'
    end
  end
  object DLessonResults: TDataSource
    DataSet = TLessonResults
    Left = 402
    Top = 300
  end
  object TLessonResults: TFDTable
    Active = True
    OnCalcFields = TLessonResultsCalcFields
    IndexFieldNames = 'idUser'
    MasterSource = DUsers
    MasterFields = 'id'
    Connection = MySQLDBConnection
    ResourceOptions.AssignedValues = [rvEscapeExpand]
    TableName = 'keytype.lessonresults'
    Left = 399
    Top = 225
    object TLessonResultsid: TFDAutoIncField
      FieldName = 'id'
      Origin = 'id'
      ReadOnly = True
    end
    object TLessonResultsidUser: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'idUser'
      Origin = 'idUser'
    end
    object TLessonResultsidLesson: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'idLesson'
      Origin = 'idLesson'
    end
    object TLessonResultslessonName: TStringField
      FieldKind = fkLookup
      FieldName = 'lessonName'
      LookupDataSet = TLessons
      LookupKeyFields = 'id'
      LookupResultField = 'name'
      KeyFields = 'idLesson'
      Lookup = True
    end
    object TLessonResultsresult: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'result'
      Origin = 'result'
      Size = 255
    end
    object TLessonResultsspeed: TBCDField
      AutoGenerateValue = arDefault
      FieldName = 'speed'
      Origin = 'speed'
      Precision = 10
      Size = 2
    end
    object TLessonResultsaccuracy: TBCDField
      AutoGenerateValue = arDefault
      FieldName = 'accuracy'
      Origin = 'accuracy'
      Precision = 10
      Size = 2
    end
    object TLessonResultsduration: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'duration'
      Origin = 'duration'
    end
    object TLessonResultsdurationHMS: TStringField
      FieldKind = fkCalculated
      FieldName = 'durationHMS'
      Calculated = True
    end
    object TLessonResultsdate: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'date'
      Origin = '`date`'
    end
    object TLessonResultsidCourse: TIntegerField
      FieldKind = fkLookup
      FieldName = 'idCourse'
      LookupDataSet = TLessons
      LookupKeyFields = 'id'
      LookupResultField = 'idCourses'
      KeyFields = 'idLesson'
      Lookup = True
    end
    object TLessonResultslessonGoal: TStringField
      FieldKind = fkLookup
      FieldName = 'lessonGoal'
      LookupDataSet = TCourses
      LookupKeyFields = 'id'
      LookupResultField = 'goal'
      KeyFields = 'idCourse'
      Lookup = True
    end
    object TLessonResultslessonGoalValue: TIntegerField
      FieldKind = fkLookup
      FieldName = 'lessonGoalValue'
      LookupDataSet = TCourses
      LookupKeyFields = 'id'
      LookupResultField = 'goalValue'
      KeyFields = 'idCourse'
      Lookup = True
    end
  end
  object IdTCPClient1: TIdTCPClient
    ConnectTimeout = 0
    Host = '127.0.0.1'
    Port = 6001
    ReadTimeout = -1
    Left = 60
    Top = 303
  end
  object DKeyStatistics: TDataSource
    DataSet = TKeyStatistics
    Left = 489
    Top = 315
  end
  object TKeyStatistics: TFDTable
    Active = True
    IndexFieldNames = 'idLessonResults'
    MasterSource = DLessonResults
    MasterFields = 'id'
    Connection = MySQLDBConnection
    ResourceOptions.AssignedValues = [rvEscapeExpand]
    TableName = 'keytype.keystatistics'
    Left = 483
    Top = 231
    object TKeyStatisticsid: TFDAutoIncField
      FieldName = 'id'
      Origin = 'id'
      ReadOnly = True
    end
    object TKeyStatisticsidLessonResults: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'idLessonResults'
      Origin = 'idLessonResults'
    end
    object TKeyStatisticskey: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'key'
      Origin = '`key`'
      FixedChar = True
      Size = 1
    end
    object TKeyStatisticscorrect: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'correct'
      Origin = 'correct'
    end
    object TKeyStatisticsmistake: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'mistake'
      Origin = 'mistake'
    end
  end
end
