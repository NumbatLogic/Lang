<?php
	class Shared_Config extends Project_Config
	{
		public function __construct($sAction)
		{
			parent::__construct($sAction);

			$this->m_xFileArray = ProjectGen_ParseDirectory(dirname(__FILE__), "/\.hpp|\.c|\.cpp$/");
		}

		public function GetName() { return "Shared"; }
		public function GetKind() { return KIND_STATIC_LIBRARY; }
		public function GetBaseDirectory() { return dirname(__FILE__); }
	}
?>