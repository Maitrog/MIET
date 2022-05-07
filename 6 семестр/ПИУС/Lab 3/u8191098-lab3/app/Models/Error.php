<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Model;

class Error extends Model
{
    public int $code;
    public string $message;
    public $meta;

    public function __construct(int $code = 400, string $message = '', $meta = null)
    {
        $this->code = $code;
        $this->message = $message;
        $this->meta = $meta;
    }
}
