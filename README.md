# scopeConfig
Scripts to automate multi-user configuration for vendor acquisition software

Vendor acqusition and analysis software generally stores configuration files in user specific or public user folders
Some configuration settings are also store in registry locations specific to the software, or can be exported using a vendor supplied utility

Logging in as an adminstrator and configuring the software then copying these files to a backup location allows us to push default settings to each user when they login
This prevents users modifying each others settings and makes backup/retrieval of default settings trivial
Settings are only pushed once for first login of user to allow the user customisation of their setup
User settings can be reset either by the user or admin by deleting their file in userlist, or optionally running a reset script

More advanced customisations and automations are possible, based on needs, however the attached scripts are a starting point

