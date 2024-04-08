#import "MacOSMessageBoxHelper.h"
#import <Cocoa/Cocoa.h>

void ShowErrorMessageBox(const std::string& errorTitle, const std::string& errorDescription) {
    NSString* title = [NSString stringWithUTF8String:errorTitle.c_str()];
    NSString* message = [NSString stringWithUTF8String:errorDescription.c_str()];

    NSAlert* alert = [[NSAlert alloc] init];
    [alert setAlertStyle:NSAlertStyleWarning];
    [alert setMessageText:title];
    [alert setInformativeText:message];
    [alert addButtonWithTitle:@"OK"];

    NSImage* icon = [NSImage imageNamed:NSImageNameCaution];
    [alert setIcon:icon];

    [alert runModal];
}