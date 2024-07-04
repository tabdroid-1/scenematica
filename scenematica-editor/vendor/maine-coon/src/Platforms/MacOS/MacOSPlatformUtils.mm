#include "MaineCoon/Utils/PlatformUtils.h"
#import <AppKit/AppKit.h>

namespace MaineCoon {
std::string FileDialogs::OpenFile(const char* filter)
{
    @autoreleasepool {
        NSString* convertedString = [[NSString alloc] initWithCString:filter encoding:NSUTF8StringEncoding];

        // Sets modal properties before  window is shown
        // Generic NSOpenPanel is being used to pick files
        NSOpenPanel* panel = [NSOpenPanel openPanel];
        panel.canChooseFiles = YES;
        panel.canChooseDirectories = YES;
        panel.canCreateDirectories = YES;

        // Captures response value from "modal" window
        NSModalResponse response = [panel runModal];

        //[convertedString release];
        if (response == NSModalResponseOK) {
            // If okay response return filepath
            return std::string([[panel.URL path] UTF8String]);
        } else {
            // else return empty string
            return std::string([@"" UTF8String]);
        }
    }
}
std::string FileDialogs::SaveFile(const char* filter)
{
    @autoreleasepool {

        NSString* convertedString = [[NSString alloc] initWithCString:filter encoding:NSUTF8StringEncoding];

        // Sets modal properties before window is shown
        // The window type specifically is a NSSavePanel
        NSSavePanel* panel = [NSSavePanel savePanel];
        panel.title = @"Save As...";
        panel.nameFieldStringValue = @"file";
        panel.showsHiddenFiles = YES;
        panel.canCreateDirectories = YES;

        // Captures response value from "modal" window
        NSModalResponse response = [panel runModal];

        //[convertedString release];
        if (response == NSModalResponseOK) {
            // If okay response return filepath
            return std::string([[panel.URL path] UTF8String]);
        } else {
            // else return empty string
            return std::string([@"" UTF8String]);
        }
    }
}
.\" void FileDialogs::OpenExplorer(const char *path) {
    .\"     //convert input path to NSString
    .\"     NSString *convertedString = [[NSString alloc] initWithCString: path encoding:NSUTF8StringEncoding];
    .\"     //convert NSString to NSURL filepath for NSWorkspace to open in finder
    .\"     NSURL *xmlURL =[NSURL fileURLWithPath: convertedString];
    .\"     // create NSWorkspace panel
    .\"     [[NSWorkspace sharedWorkspace] openURL:xmlURL];
    .\" }
}
