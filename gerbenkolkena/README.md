# Gerben Kolkena Webshop — Installatie

## Mappenstructuur na installatie

```
public_html/          ← of je webroot
├── index.php
├── checkout.php
├── mollie_return.php
├── webhook.php
├── download.php
├── .htaccess
├── orders/           ← automatisch aangemaakt, houdt orders bij
└── gerbenkolkena/
    ├── audio/        ← zet hier .wav en .mp3 bestanden
    └── video/        ← zet hier .mp4 bestanden
```

## Stap 1 — Bestanden uploaden
Upload alle PHP-bestanden en `.htaccess` naar je webroot.
Maak de map `gerbenkolkena/audio/` en `gerbenkolkena/video/` aan (of upload ze zoals gepland).

## Stap 2 — Configuratie in index.php aanpassen

```php
define('SHOP_EMAIL',  'jouw@email.nl');          // jouw e-mailadres
define('MOLLIE_KEY',  'live_xxxxxxxxxxxx');        // Mollie Live API-sleutel
define('BASE_URL',    'https://jouwdomein.nl');    // je domein zonder trailing slash
```

## Stap 3 — Mollie instellen (voor iDEAL)

1. Maak een account op https://mollie.com
2. Ga naar Dashboard → Developers → API-sleutels
3. Kopieer je **Live** sleutel (begint met `live_`)
4. Plak die in `MOLLIE_KEY` in `index.php`
5. Stel je webhook in: `https://jouwdomein.nl/webhook.php`

## Stap 4 — Bestandsrechten

```bash
chmod 700 orders/
chmod 750 gerbenkolkena/
chmod 750 gerbenkolkena/audio/
chmod 750 gerbenkolkena/video/
```

## Betaalmethoden

| Methode | Werkt meteen? | Vereiste |
|---------|---------------|----------|
| Bank (IBAN) | ✓ Ja | Niets — handmatige afhandeling |
| BUNQ betaallink | ✓ Ja | Niets — link opent bunq.me |
| iDEAL via Mollie | Na configuratie | Mollie account + Live API-sleutel |

## Beveiliging

- Bestanden in `gerbenkolkena/` zijn **niet direct** bereikbaar via de browser
- Downloads verlopen via `download.php` dat de betaalstatus controleert
- Orders worden opgeslagen als JSON in `orders/` (onzichtbaar van buiten)
- Path traversal aanvallen worden geblokkeerd

## Nieuw bestand toevoegen

Gewoon in de juiste map uploaden — de shop pikt het automatisch op.
- `.wav` en `.mp3` → `gerbenkolkena/audio/`
- `.mp4` → `gerbenkolkena/video/`
