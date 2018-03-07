# libSparkAppList
This is libSparkAppList, a super simple to implement AppList alternative for iOS 11.
**At this time only the precompiled binaries and headers are available to the public - full source code will follow soon!**

## Get Started
It's super easy to get started with libSparkAppList, let's set it up!

### Pre-Requirements
```
RocketBootstrap >= 1.0.6~Beta 1 (Available from: http://rpetri.ch/repo/)
```

### Installation for theos
Add the 'libsparkapplist.dylib' file to your "theos/lib" directory, and add the headers to "theos/include"

You will also need to add it to the libraries in your makefile
```
TWEAKNAME_LIBRARIES = sparkapplist
```

I recommend keeping to the same version of libSparkAppList for now (as I am actively improving it), so I'd point users to my repo http://beta.sparkservers.co.uk to install it.
You can add it to your control file depends like so:

```
Depends: mobilesubstrate, preferenceloader, com.spark.libsparkapplist
```


### Simple Implementation

The example below shows how to invoke the SparkAppListTableViewController, which will display a list of installed apps and enable them to be toggled.
To call the controller you just need to provide the name of the preferences plist file, and the key within the plist you want to save to - libSparkAppList handles the rest.

So for example, for my tweak Notchless my preferences file is stored at '/var/mobile/Library/Preferences/com.spark.notchlessprefs.plist' and in the key 'excludedApps'. Therefore, I provide the identifier as "com.spark.notchlessprefs" and the key as "excludedApps".

```
    #import "SparkAppListTableViewController.h"

    // Replace "com.spark.notchlessprefs" and "excludedApps" with your strings
    SparkAppListTableViewController* s = [[SparkAppListTableViewController alloc] initWithIdentifier:@"com.spark.notchlessprefs" andKey:@"excludedApps"];

	[self.navigationController pushViewController:s animated:YES];
	self.navigationItem.hidesBackButton = FALSE;
```

Add this code into a function and it can be called from your preference bundle, example:

PreferenceBundle plist (Root.plist)
```
    <dict>
	    <key>cell</key>
	    <string>PSButtonCell</string>
	    <key>label</key>
	    <string>Select apps to blacklist...</string>
	    <key>action</key>
	    <string>selectExcludeApps</string>
	</dict>
```

PreferenceBundle code (notchlessprefsRootListController.m)
```
-(void)selectExcludeApps
{
    // Replace "com.spark.notchlessprefs" and "excludedApps" with your strings
	SparkAppListTableViewController* s = [[SparkAppListTableViewController alloc] initWithIdentifier:@"com.spark.notchlessprefs" andKey:@"excludedApps"];

	[self.navigationController pushViewController:s animated:YES];
	self.navigationItem.hidesBackButton = FALSE;
}
```

Once this is implemented you can then check a bundleidentifier from within your tweak.
So an example of checking it, depending on the scenario, could be like this:

```
#import "SparkAppList.h"

%hook HOOKHERE

-(void) FUNCTIONTOHOOK
{
    NSString* bundleIdentifier = [[NSBundle mainBundle] bundleIdentifier]; // This is dependent on where it is called, may not be the correct method for your tweak!

    if([SparkAppList doesIdentifier:@"com.spark.notchlessprefs" andKey:@"excludedApps" containBundleIdentifier:bundleIdentifier]) // This returns TRUE if the bundle identifer exists
    {
        // The bundle identifier is 'on' in the list. Do whatever.
        // In the case of Notchless, this is an 'exclude' list - so I would prevent this hook from continuing and just return orig.
    }
}

%end

```

### 'Advanced' methods

If you want to add your own implementation instead of using the provided TableViewController, you can use the following methods:

```
    // Gets a list of the users apps and returns them to a handler block as an NSArray of 'SparkAppItems' (See SparkAppItem.h)
    -(void)getAppList:(void(^)(NSArray*))handler;

    // Easy to use methods to update/check the preferences file
    +(NSArray*)getAppListForIdentifier:(NSString*)identifier andKey:(NSString*)key;

    +(BOOL)doesIdentifier:(NSString*)identifier andKey:(NSString*)key containBundleIdentifier:(NSString*)bundleIdentifier;

    +(void)setAppList:(NSArray*)appList forIdentifier:(NSString*)identifier andKey:(NSString*)key;

    +(void)removeBundleID:(NSString*)bundleID forIdentifier:(NSString*)identifier andKey:(NSString*)key;

    +(void)addBundleID:(NSString*)bundleID forIdentifier:(NSString*)identifier andKey:(NSString*)key;

```

## Authors
SparkDev 2018
Inspired by rpetrich's AppList.

## License
Do What The F*ck You Want To Public License
