{
  'targets': [
    {
      'target_name': 'fbxconverter',
      'sources': [ 'CldLibAnimation.cpp',
	               'CldLibController.cpp',
				   'CldLibGeometry.cpp',
				   'CldLibImages.cpp',
				   'CldLibMaterial.cpp',
				   'CldLibParticleEffect.cpp',
				   'CldLibrary.cpp',
				   'CldLibResources.cpp',
				   'CldLibShaders.cpp',
				   'CldLibTiMaterial.cpp',
				   'CldLibUI.cpp',
				   'CldLibVisualScene.cpp',
				   'Collada.cpp',
				   'fbxasset.cpp',
				   'fbxconverter.cc',
				   'stdafx.cpp',
				   'TiFile.cpp',
				   'TiStream.cpp' 
      ],
	  
      'conditions': [
        ['OS=="win"', {
          'libraries': [
            'd:/Autodesk/FBX/FBX_SDK/2016.1.2/lib/vs2015/x64/release/libfbxsdk-md.lib'
          ],
          'include_dirs': [
            'd:/Autodesk/FBX/FBX_SDK/2016.1.2/include'
          ],
          'configurations': {
            'Debug': {
              'msvs_settings': {
                'VCCLCompilerTool': {
                  'RuntimeLibrary': 2
                }
              }
            },
            'Release': {
              'msvs_settings': {
                'VCCLCompilerTool': {
                  'RuntimeLibrary': 2
                }
              }
            }
          }
        }],
      ]
    }
  ]
}
