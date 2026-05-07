<?php
// ── Configuratie ────────────────────────────────────────────────────────────
define('SHOP_NAME',   'Gerben Kolkena');
define('PRICE',       1.00);
define('IBAN',        'NL38 BUNQ 2034 9253 27');
define('SHOP_EMAIL',  'info@gerbenkolkena.nl');   // aanpassen
define('MOLLIE_KEY',  'live_xxxxxxxxxxxxxxxxxxxx'); // aanpassen
define('BASE_DIR',    __DIR__ . '/gerbenkolkena');
define('BASE_URL',    'https://' . $_SERVER['HTTP_HOST'] . rtrim(dirname($_SERVER['SCRIPT_NAME']), '/'));

// Mappen → type
$DIRS = [
    'audio' => ['wav', 'mp3'],
    'video' => ['mp4'],
];

// ── Helpers ─────────────────────────────────────────────────────────────────
function scanFiles(array $dirs): array {
    $files = [];
    foreach ($dirs as $folder => $exts) {
        $path = BASE_DIR . '/' . $folder;
        if (!is_dir($path)) continue;
        foreach (new DirectoryIterator($path) as $f) {
            if ($f->isDot() || $f->isDir()) continue;
            $ext = strtolower($f->getExtension());
            if (in_array($ext, $exts)) {
                $files[] = [
                    'id'     => md5($folder . '/' . $f->getFilename()),
                    'name'   => $f->getFilename(),
                    'folder' => $folder,
                    'ext'    => $ext,
                    'size'   => $f->getSize(),
                    'path'   => $folder . '/' . $f->getFilename(),
                ];
            }
        }
    }
    usort($files, fn($a,$b) => strcmp($a['folder'].$a['name'], $b['folder'].$b['name']));
    return $files;
}

function formatSize(int $bytes): string {
    if ($bytes >= 1048576) return round($bytes/1048576,1) . ' MB';
    if ($bytes >= 1024)    return round($bytes/1024,1)    . ' KB';
    return $bytes . ' B';
}

function bunqLink(string $name): string {
    $desc = urlencode('Aankoop: ' . $name);
    return "https://bunq.me/gerbenkolkena/1/{$desc}";
}

// ── Routing ──────────────────────────────────────────────────────────────────
$action = $_GET['action'] ?? 'shop';

if ($action === 'checkout' && $_SERVER['REQUEST_METHOD'] === 'POST') {
    require __DIR__ . '/checkout.php';
    exit;
}
if ($action === 'mollie_return') {
    require __DIR__ . '/mollie_return.php';
    exit;
}
if ($action === 'download') {
    require __DIR__ . '/download.php';
    exit;
}

$files = scanFiles($DIRS);
?>
<!DOCTYPE html>
<html lang="nl">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title><?= SHOP_NAME ?> — Audio &amp; Video Shop</title>
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Space+Mono:wght@400;700&family=Syne:wght@400;700;800&display=swap" rel="stylesheet">
<style>
:root {
    --bg:      #0a0a0a;
    --surface: #111;
    --border:  #222;
    --accent:  #c8ff00;
    --accent2: #ff6b35;
    --text:    #e8e8e0;
    --muted:   #555;
    --radius:  4px;
}
*, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }
html { scroll-behavior: smooth; }

body {
    background: var(--bg);
    color: var(--text);
    font-family: 'Space Mono', monospace;
    font-size: 14px;
    line-height: 1.6;
    min-height: 100vh;
}

/* ── Noise overlay ── */
body::before {
    content: '';
    position: fixed;
    inset: 0;
    background-image: url("data:image/svg+xml,%3Csvg viewBox='0 0 256 256' xmlns='http://www.w3.org/2000/svg'%3E%3Cfilter id='n'%3E%3CfeTurbulence type='fractalNoise' baseFrequency='0.9' numOctaves='4' stitchTiles='stitch'/%3E%3C/filter%3E%3Crect width='100%25' height='100%25' filter='url(%23n)' opacity='0.04'/%3E%3C/svg%3E");
    pointer-events: none;
    z-index: 0;
    opacity: .5;
}

header {
    position: relative;
    z-index: 1;
    border-bottom: 1px solid var(--border);
    padding: 2rem;
    display: flex;
    justify-content: space-between;
    align-items: center;
    gap: 1rem;
    flex-wrap: wrap;
}
.logo {
    font-family: 'Syne', sans-serif;
    font-size: 1.6rem;
    font-weight: 800;
    letter-spacing: -0.02em;
    color: var(--accent);
    text-decoration: none;
}
.logo span { color: var(--text); }
.tagline {
    font-size: .75rem;
    color: var(--muted);
    letter-spacing: .12em;
    text-transform: uppercase;
}
.price-badge {
    background: var(--accent);
    color: #000;
    font-weight: 700;
    padding: .35rem .9rem;
    border-radius: var(--radius);
    font-size: .85rem;
    white-space: nowrap;
}

main {
    position: relative;
    z-index: 1;
    max-width: 1100px;
    margin: 0 auto;
    padding: 3rem 2rem 5rem;
}

.section-label {
    font-family: 'Syne', sans-serif;
    font-size: .7rem;
    letter-spacing: .2em;
    text-transform: uppercase;
    color: var(--muted);
    margin-bottom: 1.5rem;
    display: flex;
    align-items: center;
    gap: .75rem;
}
.section-label::after {
    content: '';
    flex: 1;
    height: 1px;
    background: var(--border);
}

.grid {
    display: grid;
    grid-template-columns: repeat(auto-fill, minmax(280px, 1fr));
    gap: 1px;
    background: var(--border);
    border: 1px solid var(--border);
    margin-bottom: 4rem;
}

.card {
    background: var(--surface);
    padding: 1.5rem;
    transition: background .15s;
    display: flex;
    flex-direction: column;
    gap: .75rem;
}
.card:hover { background: #161616; }

.card-top {
    display: flex;
    justify-content: space-between;
    align-items: flex-start;
    gap: .5rem;
}
.file-type {
    font-size: .65rem;
    font-weight: 700;
    letter-spacing: .15em;
    text-transform: uppercase;
    padding: .2rem .5rem;
    border-radius: 2px;
}
.type-wav  { background: #1a3a2a; color: #4ade80; }
.type-mp3  { background: #1a2a3a; color: #60a5fa; }
.type-mp4  { background: #3a1a2a; color: #f472b6; }

.file-name {
    font-family: 'Syne', sans-serif;
    font-size: 1rem;
    font-weight: 700;
    word-break: break-word;
    color: var(--text);
}
.file-meta {
    font-size: .75rem;
    color: var(--muted);
}

.card-actions {
    margin-top: auto;
    display: flex;
    gap: .5rem;
    flex-wrap: wrap;
}

.btn {
    display: inline-flex;
    align-items: center;
    gap: .4rem;
    padding: .45rem .85rem;
    border-radius: var(--radius);
    font-family: 'Space Mono', monospace;
    font-size: .75rem;
    font-weight: 700;
    cursor: pointer;
    text-decoration: none;
    border: none;
    transition: opacity .15s, transform .1s;
    white-space: nowrap;
}
.btn:hover { opacity: .85; transform: translateY(-1px); }
.btn:active { transform: translateY(0); }

.btn-iban   { background: var(--border); color: var(--text); border: 1px solid #333; }
.btn-bunq   { background: #00cc88; color: #000; }
.btn-ideal  { background: var(--accent2); color: #fff; }

/* Modal */
.modal-bg {
    display: none;
    position: fixed;
    inset: 0;
    background: rgba(0,0,0,.85);
    z-index: 100;
    align-items: center;
    justify-content: center;
    padding: 1rem;
}
.modal-bg.open { display: flex; }
.modal {
    background: var(--surface);
    border: 1px solid var(--border);
    border-radius: var(--radius);
    padding: 2rem;
    max-width: 480px;
    width: 100%;
    position: relative;
}
.modal h2 {
    font-family: 'Syne', sans-serif;
    font-size: 1.2rem;
    margin-bottom: 1rem;
    color: var(--accent);
}
.modal p { font-size: .85rem; margin-bottom: .75rem; color: #aaa; }
.iban-box {
    background: #000;
    border: 1px solid var(--accent);
    padding: .75rem 1rem;
    font-size: 1rem;
    font-weight: 700;
    letter-spacing: .05em;
    color: var(--accent);
    margin: 1rem 0;
    cursor: pointer;
    user-select: all;
}
.modal-close {
    position: absolute;
    top: 1rem; right: 1rem;
    background: none;
    border: none;
    color: var(--muted);
    font-size: 1.2rem;
    cursor: pointer;
    font-family: 'Space Mono', monospace;
}
.modal-close:hover { color: var(--text); }
.note {
    font-size: .72rem;
    color: var(--muted);
    margin-top: .5rem;
}

.empty {
    grid-column: 1/-1;
    padding: 3rem;
    text-align: center;
    color: var(--muted);
}

footer {
    position: relative;
    z-index: 1;
    border-top: 1px solid var(--border);
    padding: 1.5rem 2rem;
    text-align: center;
    font-size: .75rem;
    color: var(--muted);
}
</style>
</head>
<body>

<header>
    <div>
        <a class="logo" href="index.php">Gerben<span>Kolkena</span></a>
        <div class="tagline">Audio &amp; Video Downloads</div>
    </div>
    <div class="price-badge">€1,— per bestand</div>
</header>

<main>

<?php
$grouped = [];
foreach ($files as $f) $grouped[$f['folder']][] = $f;

foreach (['audio', 'video'] as $folder):
    $items = $grouped[$folder] ?? [];
?>
<div class="section-label"><?= strtoupper($folder) ?> (<?= count($items) ?> bestanden)</div>
<div class="grid">
<?php if (empty($items)): ?>
    <div class="empty">— Nog geen bestanden in /gerbenkolkena/<?= $folder ?>/ —</div>
<?php else: foreach ($items as $f): ?>
    <div class="card">
        <div class="card-top">
            <div class="file-name"><?= htmlspecialchars(pathinfo($f['name'], PATHINFO_FILENAME)) ?></div>
            <span class="file-type type-<?= $f['ext'] ?>">.<?= $f['ext'] ?></span>
        </div>
        <div class="file-meta"><?= formatSize($f['size']) ?> &nbsp;·&nbsp; <?= strtoupper($f['folder']) ?></div>
        <div class="card-actions">
            <button class="btn btn-iban"
                onclick="openIban(<?= json_encode($f['name']) ?>, <?= json_encode($f['id']) ?>)">
                ▤ Bank
            </button>
            <a class="btn btn-bunq"
                href="<?= htmlspecialchars(bunqLink($f['name'])) ?>"
                target="_blank" rel="noopener">
                ✦ BUNQ
            </a>
            <form method="post" action="index.php?action=checkout" style="display:inline">
                <input type="hidden" name="file_id"   value="<?= $f['id'] ?>">
                <input type="hidden" name="file_path" value="<?= htmlspecialchars($f['path']) ?>">
                <input type="hidden" name="file_name" value="<?= htmlspecialchars($f['name']) ?>">
                <button class="btn btn-ideal" type="submit">⚡ iDEAL</button>
            </form>
        </div>
    </div>
<?php endforeach; endif; ?>
</div>
<?php endforeach; ?>

</main>

<!-- IBAN Modal -->
<div class="modal-bg" id="ibanModal">
    <div class="modal">
        <button class="modal-close" onclick="closeModal()">✕</button>
        <h2>Betalen via bankoverschrijving</h2>
        <p>Maak <strong>€1,00</strong> over naar:</p>
        <div class="iban-box" onclick="copyIban(this)"><?= IBAN ?></div>
        <p>Vermeld als omschrijving:</p>
        <div class="iban-box" id="ibanRef" style="font-size:.85rem">—</div>
        <p class="note">Na ontvangst van de betaling stuur ik het bestand naar je e-mailadres. Stuur een mailtje naar <strong><?= SHOP_EMAIL ?></strong> met je betaalbewijs en gewenst bestand.</p>
    </div>
</div>

<footer>
    © <?= date('Y') ?> <?= SHOP_NAME ?> &nbsp;·&nbsp; Alle bestanden €1,— &nbsp;·&nbsp; <?= IBAN ?>
</footer>

<script>
function openIban(name, id) {
    document.getElementById('ibanRef').textContent = 'Download: ' + name.replace(/\.[^.]+$/, '');
    document.getElementById('ibanModal').classList.add('open');
}
function closeModal() {
    document.getElementById('ibanModal').classList.remove('open');
}
function copyIban(el) {
    navigator.clipboard.writeText(el.textContent.trim());
    const orig = el.textContent;
    el.textContent = '✓ Gekopieerd!';
    setTimeout(() => el.textContent = orig, 1500);
}
document.getElementById('ibanModal').addEventListener('click', function(e) {
    if (e.target === this) closeModal();
});
</script>
</body>
</html>
