Pod::Spec.new do |s|
  s.name                  = "Sempro"
  s.version               = "1.0.2"
  s.summary               = "Mondry chatbot SDK for Android"
  s.homepage              = "https://www.mondry.ai"
  s.author                = { "YOU" => "ai@sempro.no" }
  s.source 	              = { :git => "https://github.com/sempro/mondry-ios-sdk.git", :tag =>"1.0.2" }
  s.license               = { :type => "Commercial", :text => "https://datahub.sempro.ai/license" }
  s.source_files          = "Sempro.framework/Headers/Sempro.h", "Sempro.framework/Headers/MONSettings.h", "Sempro.framework/Headers/MONUser.h", "Sempro.framework/Headers/MONConversation.h", "Sempro.framework/Headers/MONMessage.h", "Sempro.framework/Headers/MONMessageAction.h", "Sempro.framework/Headers/MONConversationActivity.h", "Sempro.framework/Headers/MONCoordinates.h"
  s.preserve_paths        = "Sempro.framework/*"
  s.module_map            = "Sempro.framework/Modules/module.modulemap"
  s.frameworks            = "Sempro", "CoreText", "SystemConfiguration", "CoreTelephony", "Foundation", "CoreGraphics", "UIKit", "QuartzCore", "AssetsLibrary", "Photos", "AVFoundation", "CFNetwork"
  s.library               = "icucore"
  s.xcconfig              = { "FRAMEWORK_SEARCH_PATHS" => "$(PODS_ROOT)/Sempro" }
  s.vendored_frameworks   = "Sempro.framework"
  s.requires_arc          = true
  s.platform              = :ios
  s.ios.deployment_target = '8.0'
end